#ifndef H_REDISDAO_H_
#define H_REDISDAO_H_

#include <time.h>
#include <memory>
#include <queue>
#include <mutex>

#include "dbmodule.h"
#include "value.h"
#include "log.h"
#include "hiredis/hiredis.h"
#include "configmodule.h"

namespace db
{
    class RedisDao : public DBModule
    {
    public:
        RedisDao(void);
        ~RedisDao(void);
        /**
		* 连接到redis服务器
		*
		* @return bool
		*/
        virtual bool InitConnection(void);
        /**
		* 使用主机地址和对应的端口链接redis
		* 
		* @param host
		* @param port
		* @return bool
		*/
        virtual bool InitConnection(const string, const int, const string,const string);
        /**
		* 通过key获取对应的值
		*
		* @param key
		*/
        Value Get(string key);
        /**
		* 通过key和value将值设置到redis中
		*
		* @param key
		* @param value
		*/
        Value HGet(string key, string field);
        void Set(string, string, int = 5 * 60);
        void Del(string key);
        void Lpush(string, string);
        void Lpop(string);
        bool Exec(string);
        bool watch(string);
        bool Multi();
        int exec();


        virtual bool can_connect(void);

    private:
        RedisDao(const RedisDao &) {}
        RedisDao &operator=(const RedisDao &) { return *this; }

    private:
        redisContext *m_pConnect;
    };

    class RedisPool
    {
    public:
        ~RedisPool();

        //单例模式，获取本例的对象
        static RedisPool *Pool();
        // 关闭连接池
        static void Free();
        // 设置连接池参数
        void Init(config::ConfigModule *conf, int size = 1);
        // 创建一个连接对象
        shared_ptr<RedisDao> creatRedis();
        // 获取一个redis连接对象
        shared_ptr<RedisDao> redis();
        // 关闭连接对象,将有效的链接对象放回链接池队列中，以待下次的取用。
        void close(shared_ptr<RedisDao> conn);

    private:
        RedisPool();
        RedisPool &operator=(const RedisPool &) { return *this; }

        // 连接池是否为空
        bool isEmpty();
        // 连接池队列的队头
        shared_ptr<RedisDao> poolFront();
        // 获取连接池的大小
        int poolSize();
        // 弹出连接池队列的队头
        void poolPop();

        static RedisPool *s_pool;

        // 连接池队列
        queue<shared_ptr<RedisDao>> m_redis;
        int MAX_CONNECT;   //同时允许最大连接对象数量
        int connect_count; //目前连接池的连接对象数量
        config::ConfigModule *config;
        static std::mutex objectlock;       //对象锁
        static std::mutex poollock;         //连接池锁
        static RedisPool *mysqlpool_object; //类的对象
    };

}
#endif