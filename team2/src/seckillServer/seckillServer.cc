#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <ctime>
#include <cstdlib>

#include "Worker.h"
// #include <pthread.h>
// #include <process.h>

#include "mysql.h"
#include "hiredis.h"
#include <grpcpp/grpcpp.h>
#include "protos/SecKillService.grpc.pb.h"
#include "configmodule.h"
#include "userdao.h"
#include "gooddao.h"
#include "bagdao.h"
#include "onsalegooddao.h"
#include "tradedao.h"
#include "datetime.h"
#include "redisdao.h"

using namespace std;

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;

using myApplication::SecKillReq;
using myApplication::SecKillRsq;
using myApplication::SeckillService;

/**
 *  RPC回调方法
 */
class SecKillServiceImpl final
{
public:
    void Run(MysqlPool *mysql, RedisPool *redis)
    {
        config::ConfigModule conf;
        bool ret = conf.onLoad("./conf/config.ini");
        if (!ret)
        {
            exit(1);
            return;
        }
        string server_address = conf.getStringByKey("server_host") + ":" + conf.getStringByKey("server_port");
        ServerBuilder builder;
        SecKillServiceImpl service;

        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.RegisterService(&service_);
        builder.SetMaxReceiveMessageSize(conf.getIntByKey("max_receive_size"));
        builder.SetMaxSendMessageSize(conf.getIntByKey("max_send_size"));

        //消息队列
        cq_ = builder.AddCompletionQueue();
        redis_ = redis;

        server_ = builder.BuildAndStart();
        std::cout << "SecKillServer listening on " << server_address << std::endl;

        //入库失败的次数以及读写锁
        int failedCounter = 0;
        pthread_rwlock_t rwlock;
        pthread_rwlock_init(&rwlock, NULL);
        sucNum_ = 0;

        new Worker(&service_, cq_.get(), mysql, redis, &failedCounter, &sucNum_, &rwlock);
        //开启多线程处理rpc调用请求

        int worknum = conf.getIntByKey("worker_num");
        pthread_t tids[worknum];
        for (int i = 0; i < worknum; i++)
        {
            int ret = pthread_create(&tids[i], NULL, SecKillServiceImpl::ThreadHandlerRPC, (void *)this);
            if (ret != 0)
                std::cout << "pthread_create error: error_code=" << ret << std::endl;
        }

        //等各个线程退出后，进程才结束
        for (int i = 0; i < worknum; i++)
        {
            pthread_join(tids[i], NULL);
        }
    }

    static void *ThreadHandlerRPC(void *lparam)
    {
        SecKillServiceImpl *impl = (SecKillServiceImpl *)lparam;
        impl->HandleRPCS();
        return ((void *)0);
    }

    void HandleRPCS()
    {
        void *tag;
        bool ok;
        while (true)
        {
            if (sucNum_ < 50)
            {
                shared_ptr<RedisDao> redis = RedisPool::Pool()->redis();
                //redisReply *reply = (redisReply *)redisCommand(redisconn, "llen %s", "work_list");
                // redisReply *reply;
                redis->Exec("LLEN work_list");
                Value value = redis->Get("work_list");
                int reply = value.toInt();
                int workingNum = 0;
                if (reply != 0)
                {
                    workingNum = reply;
                    // freeReplyObject(reply);
                    if (workingNum >= 50 - sucNum_)
                    {
                        RedisPool::Pool()->close(redis);
                        continue;
                    }
                }
                RedisPool::Pool()->close(redis);
            }
            GPR_ASSERT(cq_->Next(&tag, &ok));
            GPR_ASSERT(ok);
            static_cast<Worker *>(tag)->Proceed();
        }
    }

    std::unique_ptr<ServerCompletionQueue> cq_;
    SeckillService::AsyncService service_;
    std::unique_ptr<Server> server_;
    //记录秒杀成功的个数
    int sucNum_;
    RedisPool *redis_;
};

void prepareForSeckill(MysqlPool *mymysql, RedisPool *redis)
{

    shared_ptr<RedisDao> redisconn = RedisPool::Pool()->redis();
    shared_ptr<MysqlUtil> connection = MysqlPool::Pool()->mysql();
    //  操作sql
    connection->Exec("CREATE TABLE IF NOT EXISTS specialgoods_info(g_name VARCHAR(20) NOT NULL,g_id VARCHAR(20) NOT NULL,g_totalcount INT UNSIGNED NOT NULL,PRIMARY KEY (g_id))");

    int total_count = 0;

    std::string creatGoodsTSql("CREATE TABLE IF NOT EXISTS specialgoods_info(g_name VARCHAR(20) NOT NULL,g_id VARCHAR(20) NOT NULL,g_totalcount INT UNSIGNED NOT NULL,PRIMARY KEY (g_id))");
    connection->Exec(creatGoodsTSql);
    std::string insertGoodsSql("INSERT INTO specialgoods_info(g_name, g_id, g_totalcount) VALUES('火麒麟碎片', '1311', 50) ON DUPLICATE KEY UPDATE g_id = '1311', g_totalcount = 50");
    connection->Exec(insertGoodsSql);

    //删除老的订单假数据
    std::string deleteOrderSql("DROP TABLE IF EXISTS specialorder_info");
    //connection->Exec(deleteOrderSql);

    std::string tableSql("SELECT * FROM usr_info");
    // connection->Exec(tableSql);
    vector<map<string, Value>> results = connection->Selection(tableSql);

    //往数据库中插入测试数据,模拟用户注册信息,存储用名+md5(用户名+密码+盐)
    if (results.size() == 0)
    {
        connection->Exec("CREATE TABLE usr_info(usr_name VARCHAR(100) NOT NULL,usr_key VARCHAR(100) NOT NULL,PRIMARY KEY (usr_name))");
        std::string insertSql("INSERT INTO usr_info(usr_name,usr_key) VALUES ");
        //模拟用户名为i 为方便测试，密码都设置为123456
        for (int i = 1; i <= 400; i++)
        {
            // std::string prikey = std::to_string(i) + std::to_string(i) + SALT;
            // MD5 iMD5;
            // iMD5.GenerateMD5((unsigned char *)prikey.c_str(), strlen(prikey.c_str()));
            // std::string md5_str(iMD5.ToString());

            if (i == 400)
                insertSql = insertSql + "('" + std::to_string(i) + "','" + "123456" + "')";
            else
                insertSql = insertSql + "('" + std::to_string(i) + "','" + "123456" + "'),";
        }

        std::cout << "插入的sql为" << insertSql << std::endl;
        connection->Exec(insertSql);
    }

    //查询数据库,将用户信息load到redis
    std::string searchSql("SELECT * FROM usr_info");
    // connection->Exec(searchSql);
    vector<map<string, Value>> userresults = connection->Selection(searchSql);
    vector<map<string, Value>>::const_iterator it = userresults.begin();
    while (it != userresults.end())
    {
        map<string, Value> value = *it;
        map<string, Value>::const_iterator tit = value.begin();
        string name;
        string key;
        while (tit != value.end())
        {
            if ("usr_name" == tit->first)
            {
                name = Value(tit->second).toString();
            }
            if ("usr_key" == tit->first)
            {
                key = Value(tit->second).toString();
            }
            tit++;
        }
        string action = "HMSET usr_info " + name + " " + key;
        redisconn->Exec(action);
        it++;
    }

    //查询商品数量
    std::string sql("SELECT * FROM specialgoods_info");
    // connection->Exec(sql);
    vector<map<string, Value>> goodresults = connection->Selection(sql); // 获取结果集 后释放结果集的内存
    vector<map<string, Value>>::const_iterator it2 = goodresults.begin();
    while (it2 != goodresults.end())
    {
        map<string, Value> value = *it2;
        map<string, Value>::const_iterator tit = value.begin();
        int count;
        while (tit != value.end())
        {
            if ("g_totalcount" == tit->first)
            {
                count = Value(tit->second).toInt();
            }
            tit++;
        }
        total_count = count;
        it2++;
    }

    std::string createTSql("CREATE TABLE IF NOT EXISTS specialorder_info(usr_name VARCHAR(100) NOT NULL,usr_key VARCHAR(100) NOT NULL,goods_id VARCHAR(100) NOT NULL,PRIMARY KEY (usr_name))");
    connection->Exec(createTSql);

    // redisReply *reply = NULL;
    std::string scount = std::to_string(total_count);
    string action("SET total_count " + scount);
    redisconn->Exec(action);

    Value totalcount = redisconn->Get("total_count");
    // freeReplyObject(reply);
    //redisCommand(redisconn, "DEL %s", "specialorder_info");
    redisconn->Del("specialorder_info");
    mymysql->close(connection);
    redis->close(redisconn);
}

int main(int argc, const char *argv[])
{

    //初始化数据库
    // 读取配置文件
    config::ConfigModule conf;
    conf.onLoad("./conf/config.ini");

    // 从mysql连接池选择连接
    MysqlPool *mysqlpool = MysqlPool::Pool();
    mysqlpool->Init(&conf, conf.getIntByKey("mysql_pool"));

    RedisPool *redispool = RedisPool::Pool();
    redispool->Init(&conf, conf.getIntByKey("redis_pool"));

    //准备初始数据
    prepareForSeckill(mysqlpool, redispool);
    SecKillServiceImpl server;
    SecKillRsq *reply;
    server.Run(mysqlpool, redispool);

    MysqlPool::Free();
    RedisPool::Free();

    return 0;
}