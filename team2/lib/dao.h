#ifndef H_DAO_H_
#define H_DAO_H_
#include <time.h>
#include <memory>
#include <mutex>
#include <queue>
#ifdef _cplusplus
extern "C"
{
#endif
#ifdef __linux
#include "mysql.h"

#elif __APPLE__
#include <mysql.h>

#endif
#ifdef _cplusplus
}
#endif

#include "configmodule.h"
#include "dbmodule.h"
#include "value.h"
#include "log.h"

namespace db
{

    class MysqlUtil : public DBModule
    {
    public:
        MysqlUtil(void);
        ~MysqlUtil(void);
        int ConnectionWork();
        /**
			* 连接到mysql服务器
			*
			* @return bool
			*/
        virtual bool InitConnection(void);

        /**
			* 通过数据库信息连接到数据库
			*
			* @param host		数据库服务地址
			* @param port		数据库服务端口
			* @param dbname		数据库名字
			* @param user		数据库用户
			* @param pass 		数据库密码
			* @return bool 		true:连接成功
			*/
        virtual bool InitConnection(const string, const int,
                                    const string, const string, const string);

        void setAutoCommit(int);
        void commit();
        void rollback();

        /**
			* 执行数据库SQL语句，用于更新或者是执行插入操作
			*
			* @param sql
			* @return int
			*/
        int Exec(const string);

        /**
			* 从数据库中查询数据
			* 
			* @param sql
			* return vector<map<string,Value> > 
			*/
        vector<map<string, Value>> Selection(const string);

    private:
        MysqlUtil(const MysqlUtil &) {}
        MysqlUtil &operator=(const MysqlUtil &) { return *this; }

    private:
        MYSQL m_mysql;
    };

    /**
		 * 数据库连接池
		 */
    class MysqlPool
    {
    public:
        ~MysqlPool();

        //单例模式，获取本例的对象
        static MysqlPool *Pool();
        // 关闭连接池
        static void Free();
        // 设置连接池参数
        void Init(config::ConfigModule *config, int size = 1);
        // 创建一个连接对象
        shared_ptr<MysqlUtil> creatMysql();
        // 获取一个mysql连接对象
        shared_ptr<MysqlUtil> mysql();
        // 关闭连接对象,将有效的链接对象放回链接池队列中，以待下次的取用。
        void close(shared_ptr<MysqlUtil> conn);

    private:
        MysqlPool();
        MysqlPool &operator=(const MysqlPool &) { return *this; }

        // 连接池是否为空
        bool isEmpty();
        // 连接池队列的队头
        shared_ptr<MysqlUtil> poolFront();
        // 获取连接池的大小
        int poolSize();
        // 弹出连接池队列的队头
        void poolPop();

        static MysqlPool *s_pool;

        // 连接池队列
        queue<shared_ptr<MysqlUtil>> m_mysqls;
        int MAX_CONNECT;   //同时允许最大连接对象数量
        int connect_count; //目前连接池的连接对象数量
        config::ConfigModule *config;
        static std::mutex objectlock;       //对象锁
        static std::mutex poollock;         //连接池锁
        static MysqlPool *mysqlpool_object; //类的对象
    };
}

#endif