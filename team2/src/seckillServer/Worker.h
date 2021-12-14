
#ifndef _WORKER_H
#define _WORKER_H

#include <grpc++/security/server_credentials.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc/grpc.h>
#include <grpc/support/log.h>

#include "protos/SecKillService.grpc.pb.h"

#include "../lib/dao.h"
#include "../lib/redisdao.h"
#include "Md5.h"
#include "mysql/mysql.h"
#include <thread>
#include <unistd.h>
#include <pthread.h>

#define SALT "salt"
using namespace std;
using namespace db;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;
using myApplication::SecKillReq;
using myApplication::SecKillRsq;
using myApplication::SeckillService;

class Worker
{
public:
    Worker(SeckillService::AsyncService *service, ServerCompletionQueue *cq, MysqlPool *mysql, RedisPool *redis, int *failedCount, int *successNum, pthread_rwlock_t *rwlock);

    void Proceed();

private:
    //用户权限校验
    bool checkUserInfo(std::string usr_name, std::string usr_key, shared_ptr<RedisDao> redisconn, shared_ptr<MysqlUtil> mysqlcon);
    bool checkUserInfo_mysql(std::string usr_name, std::string usr_key, shared_ptr<MysqlUtil> mysqlcon);

    //重复性校验
    bool checkUserHasGot(std::string usr_name, std::string usr_key, shared_ptr<RedisDao> redisconn, shared_ptr<MysqlUtil> mysqlcon);
    bool checkUserHasGot_mysql(std::string usr_name, std::string usr_key, shared_ptr<MysqlUtil> mysqlcon);

    //抢购过程
    void seckillGoods(std::string usr_name, std::string usr_key, shared_ptr<RedisDao> redisconn, shared_ptr<MysqlUtil> connection, int repeatCount);
    void seckillGoods_mysql(std::string usr_name, std::string usr_key, shared_ptr<MysqlUtil> connection);

    SeckillService::AsyncService *service_;
    // 消息队列
    ServerCompletionQueue *cq_;

    ServerContext ctx_;

    SecKillReq request_;

    SecKillRsq response_;

    ServerAsyncResponseWriter<SecKillRsq> responder_;

    enum WorkerStatus
    {
        CREATE,
        PROCESS,
        FINISH
    };
    // worker当前状态
    WorkerStatus status_;

    //数据库连接池
    MysqlPool *mysql_;

    //redis连接池
    RedisPool *redis_;

    //失败次数
    int *failedCount_;
    int *successNum_;
    //失败次数的读写锁
    pthread_rwlock_t *rwlock_;
};
#endif
