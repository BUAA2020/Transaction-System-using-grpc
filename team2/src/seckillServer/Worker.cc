
// #include <thread>
#include <mutex>
#include "Worker.h"
#include "log.h"

#include "const.h"

#define RETRYCOUNT 20

// bool hasStored = false;
std::mutex mtx;

Worker::Worker(SeckillService::AsyncService *service, ServerCompletionQueue *cq, MysqlPool *mysql, RedisPool *redis, int *failedCount, int *successNum, pthread_rwlock_t *rwlock)
    : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE), mysql_(mysql), redis_(redis), failedCount_(failedCount), successNum_(successNum), rwlock_(rwlock)
{
  Proceed();
}

void Worker::Proceed()
{
  if (status_ == CREATE)
  {

    status_ = PROCESS;
    service_->RequestdoSecKill(&ctx_, &request_, &responder_, cq_, cq_, this);
  }
  else if (status_ == PROCESS)
  {
    //连接redis
    shared_ptr<RedisDao> redisconn = redis_->redis();
    shared_ptr<MysqlUtil> mysqlconnection = mysql_->mysql();
    status_ = FINISH;
    redisconn->Lpush("work_list", to_string(1));
    new Worker(service_, cq_, mysql_, redis_, failedCount_, successNum_, rwlock_);

    auto usr_name = request_.username();
    auto usr_key = request_.password();

    // 用于调试，打印出线程信息
    std::thread::id tid = std::this_thread::get_id();
    cout << "Current thread id : " << tid << endl;

    //用户名权限校验
    if (checkUserInfo(usr_name, usr_key, redisconn, mysqlconnection))
    {
      //重复性校验
      if (!checkUserHasGot(usr_name, usr_key, redisconn, mysqlconnection))
      {
        //开始抢购
        seckillGoods(usr_name, usr_key, redisconn, mysqlconnection, 0);
      }
      else
      {
        Log::Print(__func__, "Seckill failed!!! usr has got!");
        response_.set_status(Const::StatusCode::SECKILL_FAILD);
        response_.set_message(Const::GetStatusMsg(Const::StatusCode::SECKILL_FAILD));
      }
    }
    else
    {
      Log::Print(__func__, "Seckill failed!!! usr has noprimit");
      response_.set_status(Const::StatusCode::SECKILL_FAILD);
      response_.set_message(Const::GetStatusMsg(Const::StatusCode::SECKILL_FAILD));
    }
    redis_->close(redisconn);
    mysql_->close(mysqlconnection);
    responder_.Finish(response_, Status::OK, this);
  }
  else
  {
    GPR_ASSERT(status_ == FINISH);
    shared_ptr<RedisDao> redisconn = redis_->redis();
    redisconn->Lpop("work_list");
    redis_->close(redisconn);
    delete this;
  }
}

bool Worker::checkUserInfo(std::string usr_name, std::string usr_key, shared_ptr<RedisDao> redisconn, shared_ptr<MysqlUtil> mysqlcon)
{
  if (redisconn == nullptr)
  {
    return checkUserInfo_mysql(usr_name, usr_key, mysqlcon);
  }
  Value res = redisconn->HGet("usr_info", usr_name);
  string confirmReply = res.toString();
  if (confirmReply != "0")
  {
    if (usr_key == confirmReply)
    {
      return true;
    }
  }
  return false;
}

bool Worker::checkUserInfo_mysql(std::string usr_name, std::string usr_key, shared_ptr<MysqlUtil> mysqlcon)
{
  bool isUsr = false;
  string selSql("SELECT usr_key FROM usr_info WHERE usr_name " + usr_name);
  vector<map<string, Value>> temp = mysqlcon->Selection(selSql);
  if (temp.size() == 0)
  {
    Log::Perror(__func__, "selSql usr_key was Error ! ");
    return false;
  }
  vector<map<string, Value>>::const_iterator it = temp.begin();
  while (it != temp.end())
  {
    map<string, Value> value = *it;
    map<string, Value>::const_iterator tit = value.begin();
    while (tit != value.end())
    {
      if ("usr_key" == tit->first)
      {
        if (Value(tit->second).toString() == usr_key)
        {
          isUsr = true;
        }
      }
      tit++;
    }
    it++;
  }
  return isUsr;
}

bool Worker::checkUserHasGot(std::string usr_name, std::string usr_key, shared_ptr<RedisDao> redisconn, shared_ptr<MysqlUtil> mysqlcon)
{
  if (redisconn == nullptr)
  {
    return checkUserHasGot_mysql(usr_name, usr_key, mysqlcon);
    ;
  }
  Value res = redisconn->HGet("specialorder_info", usr_name);
  string orderReply = res.toString();
  if (orderReply != "0")
  {
    return true;
  }
  return false;
}

bool Worker::checkUserHasGot_mysql(std::string usr_name, std::string usr_key, shared_ptr<MysqlUtil> mysqlcon)
{
  bool hasgot = false;
  // bool isSuc = true;
  int ON = 1;
  int OFF = 0;
  mysqlcon->setAutoCommit(OFF);
  string selSql("SELECT * FROM specialorder_info WHERE usr_name =" + usr_name + "FOR UPDATE");
  vector<map<string, Value>> temp = mysqlcon->Selection(selSql);
  if (temp.size() == 0)
  {
    Log::Perror(__func__, "selSql usr_key was Error ! ");
    hasgot = false;
  }
  else
  {
    hasgot = true;
  }

  // if(!isSuc)
  // {
  //   mysql_rollback(connection);
  //   pthread_rwlock_wrlock(rwlock_);
  //   ++ *failedCount_;
  //   pthread_rwlock_unlock(rwlock_);

  //   response_.set_result("0");
  // }
  // else
  // {
  //   mysql_commit(connection);
  //   response_.set_result("1");
  //   std::cout << "Seckill Succeed!!!" <<std::endl;
  // }
  mysqlcon->setAutoCommit(ON);
  return hasgot;
}

void Worker::seckillGoods(std::string usr_name, std::string usr_key, shared_ptr<RedisDao> redisconn, shared_ptr<MysqlUtil> mysqlcon, int repeatCount)
{
  if (redisconn == nullptr)
  {
    seckillGoods_mysql(usr_name, usr_key, mysqlcon);
    return;
  }
  ++repeatCount;
  Log::Print(__func__, "Start shopping! ");
  int currGoods_count = 0;
  bool ret = redisconn->watch("total_count");
  Value res = redisconn->Get("total_count");
  int reply = res.toInt();
  if (reply != 0 && ret == true)
  {
    currGoods_count = reply;
  }
  else
  {
    response_.set_status(Const::StatusCode::SECKILL_FAILD);
    response_.set_message(Const::GetStatusMsg(Const::StatusCode::SECKILL_FAILD));
    return;
  }
  if (currGoods_count >= 0)
  {
    //开启事务
    if (redisconn->Multi())
    {
      //订单操作
      string sql("DECR total_count");
      redisconn->Exec(sql);
      redisconn->Exec("HMSET specialorder_info " + usr_name + ' ' + usr_key);

      int execReply = redisconn->exec();

      if (execReply >= 1)
      {
        redisconn->Exec("UNWATCH");
        // 与mysql验证并更新mysql
        seckillGoods_mysql(usr_name, usr_key, mysqlcon);
        return;
      }
      else
      {
        //失败重试
        Log::Print(__func__, "Retry! ");
        redisconn->Exec("UNWATCH");
        if (repeatCount < RETRYCOUNT)
        {
          seckillGoods(usr_name, usr_key, redisconn, mysqlcon, repeatCount);
        }
        else
        {
          response_.set_status(Const::StatusCode::SECKILL_FAILD);
          response_.set_message(Const::GetStatusMsg(Const::StatusCode::SECKILL_FAILD));
        }
      }
    }
    else
    {
      redisconn->Exec("UNWATCH");
      if (repeatCount < RETRYCOUNT)
      {
        seckillGoods(usr_name, usr_key, redisconn, mysqlcon, repeatCount);
      }
      else
      {
        response_.set_status(Const::StatusCode::SECKILL_FAILD);
        response_.set_message(Const::GetStatusMsg(Const::StatusCode::SECKILL_FAILD));
      }
    }
    return;
  }
  else
  {
    redisconn->Exec("UNWATCH");
    pthread_rwlock_wrlock(rwlock_);
    if (*failedCount_ > 0)
    {

      std::string failedC = std::to_string(*failedCount_);

      redisconn->Exec("SET total_count " + failedC);
      // redisReply *setCreply = (redisReply *)redisCommand(redisconn, "SET total_count %s", failedC.c_str());
      // if (setCreply != NULL && setCreply->type == REDIS_REPLY_STATUS && (strcasecmp(setCreply->str, "OK") == 0))
      if (redisconn->Exec("SET total_count" + failedC))
      {
        *failedCount_ = 0;
      }
    }
    pthread_rwlock_unlock(rwlock_);

    response_.set_status(Const::StatusCode::SECKILL_FAILD);
    response_.set_message(Const::GetStatusMsg(Const::StatusCode::SECKILL_FAILD));
    std::cout << "seckill failed! The goods has sold out!" << std::endl;
    return;
  }
}

void Worker::seckillGoods_mysql(std::string usr_name, std::string usr_key, shared_ptr<MysqlUtil> mysqlcon)
{
  bool isSuc = true;
  int ON = 1;
  int OFF = 0;
  mysqlcon->setAutoCommit(OFF);
  int total_count = 0;
  std::string selSql("SELECT g_totalcount FROM specialgoods_info WHERE g_id ='1311' FOR UPDATE");
  vector<map<string, Value>> temp = mysqlcon->Selection(selSql);
  if (temp.size() == 0)
  {
    Log::Perror(__func__, "SelSql was Error");
    isSuc = false;
  }
  else
  {
    vector<map<string, Value>>::const_iterator it = temp.begin();
    while (it != temp.end())
    {
      map<string, Value> value = *it;
      map<string, Value>::const_iterator tit = value.begin();
      while (tit != value.end())
      {
        if ("g_totalcount" == tit->first)
        {
          total_count = atoi(Value(tit->second).toString().c_str());
        }
        tit++;
      }
      it++;
    }
    if (total_count > 0)
    {
      --total_count;
    }
    else
    {
      // mysql_rollback(connection);
      response_.set_status(Const::StatusCode::SECKILL_FAILD);
      response_.set_message(Const::GetStatusMsg(Const::StatusCode::SECKILL_FAILD));
      mysqlcon->setAutoCommit(ON);
      return;
    }
    string updateSql("UPDATE specialgoods_info SET g_totalcount =" + to_string(total_count) + " " + "WHERE g_id = '1311' ");
    if (mysqlcon->Exec(updateSql) == 0)
    {
      Log::Perror(__func__, "updateSql was error");
      isSuc = false;
    }
    string insertOSql = "INSERT INTO specialorder_info(usr_name,usr_key,goods_id) VALUES ('" + usr_name + "','" + usr_key + "','1311')";
    if (mysqlcon->Exec(insertOSql) == 0)
    {
      Log::Perror(__func__, "insertOSql was error");
      isSuc = false;
    }

    if (!isSuc)
    {
      mysqlcon->rollback();
      pthread_rwlock_wrlock(rwlock_);
      ++*failedCount_;
      pthread_rwlock_unlock(rwlock_);

      response_.set_status(Const::StatusCode::SECKILL_FAILD);
      response_.set_message(Const::GetStatusMsg(Const::StatusCode::SECKILL_FAILD));
    }
    else
    {
      mysqlcon->commit();
      response_.set_status(Const::StatusCode::OK);
      response_.set_message(Const::GetStatusMsg(Const::StatusCode::OK));
      ++*successNum_;
      std::cout << "Seckill Succeed!!!" << std::endl;
    }
    mysqlcon->setAutoCommit(ON);
  }
}