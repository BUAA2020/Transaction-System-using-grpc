#include "dao.h"

namespace db
{

    MysqlUtil::MysqlUtil(void)
    {
        mysql_init(&this->m_mysql);
        this->m_isopen = false;
    }

    MysqlUtil::~MysqlUtil(void)
    {
        mysql_close(&this->m_mysql);
        this->m_isopen = false;
    }
    int MysqlUtil::ConnectionWork()
    {
        return mysql_ping(&this->m_mysql);
    }

    bool MysqlUtil::InitConnection(void)
    {
        if (this->m_isopen)
        {
            Log::Warning(__func__, "Is connected to server!");

            return true;
        }

        if (!this->can_connect())
        {
            Log::Perror(__func__, "Can't connection databases, param error!");

            return false;
        }

        if (!mysql_real_connect(
                &this->m_mysql,
                this->GetHost().c_str(),
                this->GetUser().c_str(),
                this->GetPass().c_str(),
                this->GetDbName().c_str(),
                this->GetPort(), nullptr, 0))
        {
            Log::Perror(__func__, "Error connection to database:" +
                                      string(mysql_error(&this->m_mysql)));

            return false;
        }

        this->m_isopen = true;

        Log::Print(__func__, this->toString() + " Connect  Mysql Success!");

        return true;
    }

    bool MysqlUtil::InitConnection(const string host, const int port,
                                   const string dbname, const string user, const string pass)
    {
        if (this->m_isopen)
        {
            Log::Warning(__func__, "Is connected to server!");

            return true;
        }

        this->SetHost(host);
        this->SetPort(port);
        this->SetDbName(dbname);
        this->SetUser(user);
        this->SetPass(pass);

        if (!this->can_connect())
        {
            Log::Perror(__func__, "Can't connection database ,param error!");
        }

        if (!mysql_real_connect(
                &this->m_mysql,
                this->GetHost().c_str(),
                this->GetUser().c_str(),
                this->GetPass().c_str(),
                this->GetDbName().c_str(),
                this->GetPort(), nullptr, 0))
        {
            Log::Perror(__func__, "Error connection to database:" +
                                      string(mysql_error(&this->m_mysql)));

            return false;
        }

        this->m_isopen = true;

        return true;
    }

    void MysqlUtil::setAutoCommit(int isOff)
    {
        mysql_autocommit(&this->m_mysql, isOff);
        return;
    }

    void MysqlUtil::rollback()
    {
        mysql_rollback(&this->m_mysql);
        return;
    }
    void MysqlUtil::commit()
    {
        mysql_commit(&this->m_mysql);
        return;
    }

    int MysqlUtil::Exec(const string sql)
    {
        if (0 == sql.size())
        {
            return 0;
        }
        Log::Print(__func__, sql);
        if (!this->m_isopen)
        {
            Log::Perror(__func__, "Mysql connection isn't opened!");

            return 0;
        }

        int rows = 0;
        mysql_query(&this->m_mysql, "set names utf8");
        int res = mysql_query(&this->m_mysql, sql.c_str());
        if (res >= 0)
        {
            rows = mysql_affected_rows(&this->m_mysql);
            if (-1 == rows)
            {
                Log::Perror(__func__, "ExecSQL error :" +
                                          string(mysql_error(&this->m_mysql)));
            }

            return rows;
        }
        else
        {
            Log::Perror(__func__, "Update errpr :" +
                                      string(mysql_error(&this->m_mysql)));

            return 0;
        }

        return rows;
    }

    vector<map<string, Value>> MysqlUtil::Selection(const string sql)
    {
        vector<map<string, Value>> results;
        if (0 == sql.size())
        {
            return results;
        }

        Log::Print(__func__, sql);

        if (!this->m_isopen)
        {
            Log::Perror(__func__, "Mysql connection isn't opened!");

            return results;
        }

        int i, j = 0;
        mysql_query(&this->m_mysql, "set names utf8");
        i = mysql_real_query(&this->m_mysql, sql.c_str(), sql.size());
        if (i != 0)
        {
            Log::Perror(__func__, "Select Error!" + string(mysql_error(&this->m_mysql)));

            return results;
        }

        MYSQL_RES *res;
        MYSQL_ROW row;
        MYSQL_FIELD *fd;

        res = mysql_store_result(&this->m_mysql);
        vector<string> fild_name;
        for (i = 0; nullptr != (fd = mysql_fetch_field(res)); i++)
        {
            fild_name.push_back(string(fd->name));
        }

        map<string, Value> objectValue;
        while ((row = mysql_fetch_row(res)))
        {
            int fields = mysql_num_fields(res);

            /**
				* 将查询到的值放入值匹配其中
				*/
            for (j = 0; j < fields; j++)
            {
                Value _value;
                _value.SetValue(row[j]);
                objectValue[fild_name[j]] = _value;
            }

            results.push_back(objectValue);
            objectValue.clear();
        }

        mysql_free_result(res);

        return results;
    }

    MysqlPool *MysqlPool::s_pool = nullptr;
    std::mutex MysqlPool::objectlock;
    std::mutex MysqlPool::poollock;

    MysqlPool *MysqlPool::Pool()
    {
        if (nullptr != MysqlPool::s_pool)
        {
            return MysqlPool::s_pool;
        }
        objectlock.lock();
        MysqlPool::s_pool = new MysqlPool();
        objectlock.unlock();
        return MysqlPool::s_pool;
    }

    void MysqlPool::Free()
    {
        objectlock.lock();
        while (MysqlPool::s_pool->poolSize() != 0)
        {
            MysqlPool::s_pool->poolFront()->~MysqlUtil();
            MysqlPool::s_pool->poolPop();
            MysqlPool::s_pool->connect_count--;
        }
        delete MysqlPool::s_pool;
        MysqlPool::s_pool = nullptr;
        objectlock.unlock();
    }

    MysqlPool::MysqlPool()
    {
    }

    MysqlPool::~MysqlPool()
    {
    }

    void MysqlPool::Init(config::ConfigModule *config, int size /* = 1 */)
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
        // for (int i = 0; i < size; ++i)
        // {
        //     shared_ptr<MysqlUtil> mysql(new MysqlUtil);
        //     mysql->SetHost(config->getStringByKey("mysql_host"));
        //     mysql->SetPort(config->getIntByKey("mysql_port"));
        //     mysql->SetPass(config->getStringByKey("mysql_pass"));
        //     mysql->SetDbName(config->getStringByKey("mysql_db"));
        //     mysql->SetUser(config->getStringByKey("mysql_user"));
        //     mysql->InitConnection();
        //     this->m_mysqls.push(mysql);
        // }
        return;
    }
    bool MysqlPool::isEmpty()
    {
        return m_mysqls.empty();
    }
    shared_ptr<MysqlUtil> MysqlPool::poolFront()
    {
        return m_mysqls.front();
    }
    int MysqlPool::poolSize()
    {
        return m_mysqls.size();
    }

    void MysqlPool::poolPop()
    {
        m_mysqls.pop();
    }

    shared_ptr<MysqlUtil> MysqlPool::creatMysql()
    {
        shared_ptr<MysqlUtil> mysql(new MysqlUtil);
        mysql->SetHost(config->getStringByKey("mysql_host"));
        mysql->SetPort(config->getIntByKey("mysql_port"));
        mysql->SetPass(config->getStringByKey("mysql_pass"));
        mysql->SetDbName(config->getStringByKey("mysql_db"));
        mysql->SetUser(config->getStringByKey("mysql_user"));
        if (!mysql->InitConnection())
        {
            return nullptr;
        }
        this->connect_count++;
        return mysql;
    }

    shared_ptr<MysqlUtil> MysqlPool::mysql()
    {
        poollock.lock();
        shared_ptr<MysqlUtil> conn;
        if (!isEmpty())
        {
            // 将断开的连接从池中取出
            while (!isEmpty() && poolFront()->ConnectionWork())
            {
                poolFront()->~MysqlUtil();
                poolPop();
                this->connect_count--;
            }
            if (!isEmpty())
            {
                conn = poolFront();
                poolPop();
            }
            else
            {
                if (this->connect_count < this->MAX_CONNECT)
                {
                    conn = creatMysql();
                }
                else
                {
                    Log::Perror(__func__, "The number of mysql connections is too much!");
                }
            }
        }
        else
        {
            if (this->connect_count < this->MAX_CONNECT)
            {
                conn = creatMysql();
            }
            else
            {
                Log::Perror(__func__, "The number of mysql connections is too much!");
            }
        }
        poollock.unlock();
        return conn;
    }

    void MysqlPool::close(shared_ptr<MysqlUtil> conn)
    {
        if (conn != NULL)
        {
            poollock.lock();
            m_mysqls.push(conn);
            poollock.unlock();
        }
    }

}