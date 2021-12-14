#include "redisdao.h"

namespace db
{
    RedisDao::RedisDao(void)
    {
        this->m_pConnect = nullptr;
        this->m_isopen = false;
    }
    RedisDao::~RedisDao(void)
    {
        if (nullptr != this->m_pConnect)
        {
            redisFree(this->m_pConnect);
            this->m_pConnect = nullptr;
        }
        this->m_isopen = false;
    }
    bool RedisDao::InitConnection(void)
    {
        if (nullptr != this->m_pConnect)
        {
            Log::Warning(__func__, "Redis already create instance!");
            return true;
        }
        if (this->m_isopen)
        {
            Log::Warning(__func__, "Is connected to Redis!");
            return true;
        }
        if (!this->can_connect())
        {
            Log::Perror(__func__, "Can't connection Redis, param error!");
            return false;
        }
        this->m_pConnect = redisConnect(this->GetHost().c_str(),
                                        this->GetPort());
        if (this->GetPass() != "")
        {
            std::string pass = "AUTH " + this->GetPass();
            redisCommand(this->m_pConnect, pass.c_str());
        }
        if (this->GetDbName() != "")
        {
            std::string db = "SELECT " + this->GetDbName();
            redisCommand(this->m_pConnect, db.c_str());
        }

        if (this->m_pConnect != nullptr && this->m_pConnect->err)
        {
            Log::Perror(__func__, "Connect Redis error! msg:" +
                                      string(this->m_pConnect->errstr));
            return false;
        }
        Log::Print(__func__, this->toString() + " Connect Redis Success!");
        this->m_isopen = true;
        return true;
    }
    bool RedisDao::InitConnection(const string host, const int port, const string dbname, const string pass)
    {
        if (nullptr != this->m_pConnect)
        {
            Log::Warning(__func__, "Redis already create instance!");
            return true;
        }
        if (this->m_isopen)
        {
            Log::Warning(__func__, "Is connected to Redis!");
            return true;
        }
        this->SetHost(host);
        this->SetPort(port);
        this->SetDbName(dbname);
        this->SetPass(pass);

        if (!this->can_connect())
        {
            Log::Perror(__func__, "Can't connection Redis, param error!");
            return false;
        }
        this->m_pConnect = redisConnect(this->GetHost().c_str(),
                                        this->GetPort());

        string auth = "Auth " + this->GetPass();
        redisReply *reply;
        reply = (redisReply *)redisCommand(this->m_pConnect, auth.c_str());

        if (this->m_pConnect != nullptr && this->m_pConnect->err)
        {
            Log::Perror(__func__, "Connect Redis error! msg:" +
                                      string(this->m_pConnect->errstr));
            return false;
        }
        this->m_isopen = true;
        return true;
    }
    Value RedisDao::Get(string key)
    {
        Value _value;
        if (0 == key.size())
        {
            return _value;
        }
        if (!this->m_isopen)
        {
            Log::Perror(__func__, "Redis connection isn't opened!");
            return _value;
        }
        string action = "GET " + key;
        Log::Print(__func__, action);
        redisReply *_reply;
        _reply = (redisReply *)redisCommand(this->m_pConnect, action.c_str());
        // Log::Print(__func__, _reply->type);
        if (nullptr != _reply && _reply->type != REDIS_REPLY_ERROR)
        {
            string res;
            if (_reply->type == REDIS_REPLY_NIL)
            {
                res = "0";
            }
            else
            {
                res = _reply->str;
            }
            freeReplyObject(_reply);
            _value.SetValue(res);
        }
        else
        {
            Log::Perror(__func__, "Redis error :" + string(this->m_pConnect->errstr));
            freeReplyObject(_reply);
        }
        return _value;
    }
    Value RedisDao::HGet(string key, string field)
    {
        Value _value;
        if (0 == key.size())
        {
            return _value;
        }
        if (!this->m_isopen)
        {
            Log::Perror(__func__, "Redis connection isn't opened!");
            return _value;
        }

        string action = " HGET " + key + " " + field;
        Log::Print(__func__, action);
        redisReply *_reply;
        _reply = (redisReply *)redisCommand(this->m_pConnect, action.c_str());
        if (nullptr != _reply && _reply->type != REDIS_REPLY_ERROR)
        {
            string res;
            if (_reply->type == REDIS_REPLY_NIL)
            {
                res = "0";
            }
            else
            {
                res = _reply->str;
            }
            freeReplyObject(_reply);
            _value.SetValue(res);
        }
        else
        {
            Log::Perror(__func__, "Redis  error :" + string(this->m_pConnect->errstr));
            freeReplyObject(_reply);
        }
        return _value;
    }

    void RedisDao::Set(string key, string value, int expire_time)
    {
        if (0 == key.size() || 0 == value.size())
        {
            return;
        }
        if (!this->m_isopen)
        {
            Log::Perror(__func__, "Redis connection isn't opened!");
            return;
        }

        string action = "SET " + key + " " + value;
        Log::Print(__func__, action);
        redisReply *reply = (redisReply *)redisCommand(this->m_pConnect, action.c_str());
        if (reply != NULL && reply->type == REDIS_REPLY_STATUS && (strcasecmp(reply->str, "OK") == 0))
        {
            freeReplyObject(reply);
        }
        else
        {
            Log::Perror(__func__, "Redis error :" + string(this->m_pConnect->errstr));
            freeReplyObject(reply);
            return;
        }

        // 此处设置过期时间
        string action1 = "EXPIRE " + key + " " + to_string(expire_time);
        Log::Print(__func__, action1);
        redisReply *reply1 = (redisReply *)redisCommand(this->m_pConnect, action1.c_str());
        if (reply1 != NULL && reply1->type == REDIS_REPLY_STATUS && (strcasecmp(reply1->str, "OK") == 0))
        {
            freeReplyObject(reply1);
        }
        else
        {
            Log::Perror(__func__, "Redis error :" + string(this->m_pConnect->errstr));
            freeReplyObject(reply1);
            return;
        }
        return;
    }

    void RedisDao::Lpush(string key, string value)
    {
        if (0 == key.size() || 0 == value.size())
        {
            return;
        }
        if (!this->m_isopen)
        {
            Log::Perror(__func__, "Redis connection isn't opened!");
            return;
        }
        string action = "LPUSH " + key + " " + value;
        Log::Print(__func__, action);
        redisReply *reply = (redisReply *)redisCommand(this->m_pConnect, action.c_str());

        if (reply != NULL && reply->type != REDIS_REPLY_ERROR)
        {
            freeReplyObject(reply);
            return;
        }
        else
        {
            Log::Perror(__func__, "Redis error :" + string(this->m_pConnect->errstr));
            freeReplyObject(reply);
        }
        return;
    }

    void RedisDao::Del(string key)
    {
        if (0 == key.size())
        {
            return;
        }
        if (!this->m_isopen)
        {
            Log::Perror(__func__, "Redis connection isn't opened!");
            return;
        }
        string action = "DEL " + key;
        Log::Print(__func__, action);
        redisReply *reply = (redisReply *)redisCommand(this->m_pConnect, action.c_str());
        if (reply != NULL && reply->type != REDIS_REPLY_ERROR)
        {
            freeReplyObject(reply);
            return;
        }
        else
        {
            Log::Perror(__func__, "Redis  error :" + string(this->m_pConnect->errstr));
            freeReplyObject(reply);
        }
        return;
    }
    void RedisDao::Lpop(string key)
    {
        if (0 == key.size())
        {
            return;
        }
        if (!this->m_isopen)
        {
            Log::Perror(__func__, "Redis connection isn't opened!");
            return;
        }
        string action = "LPOP " + key;
        Log::Print(__func__, action);
        redisReply *reply = (redisReply *)redisCommand(this->m_pConnect, action.c_str());
        if (reply != NULL && reply->type != REDIS_REPLY_ERROR)
        {
            freeReplyObject(reply);
            return;
        }
        else
        {
            Log::Perror(__func__, "Redis error :" + string(this->m_pConnect->errstr));
            freeReplyObject(reply);
        }
        return;
    }

    bool RedisDao::Exec(string action)
    {
        if (0 == action.size())
        {
            return false;
        }
        if (!this->m_isopen)
        {
            Log::Perror(__func__, "Redis connection isn't opened!");
            return false;
        }
        Log::Print(__func__, action);
        redisReply *reply = (redisReply *)redisCommand(this->m_pConnect, action.c_str());
        // Log::Print(__func__, reply->type);
        if (reply != NULL && reply->type != REDIS_REPLY_ERROR)
        {
            freeReplyObject(reply);
            return true;
        }
        else
        {
            Log::Perror(__func__, "Redis  error :" + string(this->m_pConnect->errstr));
            freeReplyObject(reply);
        }

        return false;
    }

    bool RedisDao::watch(string key)
    {
        if (0 == key.size())
        {
            return false;
        }
        if (!this->m_isopen)
        {
            Log::Perror(__func__, "Redis connection isn't opened!");
            return false;
        }
        string action = "WATCH " + key;
        Log::Print(__func__, action);
        redisReply *reply = (redisReply *)redisCommand(this->m_pConnect, action.c_str());
        if (reply != NULL && reply->type != REDIS_REPLY_ERROR)
        {
            freeReplyObject(reply);
            return true;
        }
        else
        {
            Log::Perror(__func__, "Redis  error :" + string(this->m_pConnect->errstr));
            freeReplyObject(reply);
        }
        return false;
    }

    bool RedisDao::Multi()
    {
        if (!this->m_isopen)
        {
            Log::Perror(__func__, "Redis connection isn't opened!");
            return false;
        }
        string action = "MULTI";
        Log::Print(__func__, action);
        redisReply *reply = (redisReply *)redisCommand(this->m_pConnect, action.c_str());
        if (reply != NULL && reply->type != REDIS_REPLY_ERROR)
        {
            freeReplyObject(reply);
            return true;
        }
        else
        {
            Log::Perror(__func__, "Redis  error :" + string(this->m_pConnect->errstr));
            freeReplyObject(reply);
        }
        return false;
    }

    int RedisDao::exec()
    {
        if (!this->m_isopen)
        {
            Log::Perror(__func__, "Redis connection isn't opened!");
            return 0;
        }
        Log::Print(__func__, "EXEC");
        redisReply *execReply = (redisReply *)redisCommand(this->m_pConnect, "EXEC");
        if (execReply != NULL && execReply->type == REDIS_REPLY_ARRAY)
        {
            freeReplyObject(execReply);
            return execReply->elements;
        }
        else
        {
            Log::Perror(__func__, "Redis error :" + string(this->m_pConnect->errstr));
            freeReplyObject(execReply);
        }
        return 0;
    }

    bool RedisDao::can_connect(void)
    {
        if (0 == this->GetHost().size() ||
            !this->GetPort())
        {

            return false;
        }
        return true;
    }

    RedisPool *RedisPool::s_pool = nullptr;
    std::mutex RedisPool::objectlock;
    std::mutex RedisPool::poollock;

    RedisPool *RedisPool::Pool()
    {
        if (nullptr != RedisPool::s_pool)
        {
            return RedisPool::s_pool;
        }
        objectlock.lock();
        RedisPool::s_pool = new RedisPool();
        objectlock.unlock();
        return RedisPool::s_pool;
    }
    void RedisPool::Free()
    {
        if (nullptr == RedisPool::s_pool)
        {
            return;
        }
        objectlock.lock();
        while (RedisPool::s_pool->poolSize() != 0)
        {
            RedisPool::s_pool->poolFront()->~RedisDao();
            RedisPool::s_pool->poolPop();
            RedisPool::s_pool->connect_count--;
        }
        delete RedisPool::s_pool;
        RedisPool::s_pool = nullptr;
        objectlock.unlock();
    }
    RedisPool::RedisPool()
    {
    }
    RedisPool::~RedisPool()
    {
    }
    void RedisPool::Init(config::ConfigModule *config, int size /* = 1 */)
    {
        if (nullptr == config)
        {
            return;
        }
        if (1 > size)
        {
            size = 1;
        }
        if (500 < size)
        {
            size = 500;
        }
        this->MAX_CONNECT = size;
        this->connect_count = 0;
        this->config = config;

        return;
    }
    bool RedisPool::isEmpty()
    {
        return m_redis.empty();
    }
    shared_ptr<RedisDao> RedisPool::poolFront()
    {
        return m_redis.front();
    }
    int RedisPool::poolSize()
    {
        return m_redis.size();
    }

    void RedisPool::poolPop()
    {
        m_redis.pop();
    }

    shared_ptr<RedisDao> RedisPool::creatRedis()
    {
        shared_ptr<RedisDao> redis(new RedisDao);
        redis->SetHost(config->getStringByKey("redis_host"));
        redis->SetPort(config->getIntByKey("redis_port"));
        redis->SetPass(config->getStringByKey("redis_pass"));
        redis->SetDbName(config->getStringByKey("redis_db"));
        if (!redis->InitConnection())
        {
            return nullptr;
        }
        this->connect_count++;
        return redis;
    }

    shared_ptr<RedisDao> RedisPool::redis()
    {
        poollock.lock();
        shared_ptr<RedisDao> conn;
        if (!isEmpty())
        {
            if (!isEmpty())
            {
                conn = poolFront();
                poolPop();
            }
            else
            {
                if (this->connect_count < this->MAX_CONNECT)
                {
                    conn = creatRedis();
                }
                else
                {
                    Log::Perror(__func__, "The number of redis connections is too much!");
                }
            }
        }
        else
        {
            if (this->connect_count < this->MAX_CONNECT)
            {
                conn = creatRedis();
            }
            else
            {
                Log::Perror(__func__, "The number of redis connections is too much!");
            }
        }
        poollock.unlock();
        return conn;
    }

    // 将有效的链接对象放回链接池队列中，以待下次的取用。
    void RedisPool::close(shared_ptr<RedisDao> conn)
    {
        if (conn != NULL)
        {
            poollock.lock();
            m_redis.push(conn);
            poollock.unlock();
        }
    }
}
