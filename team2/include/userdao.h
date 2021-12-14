#ifndef H_USER_H_
#define H_USER_H_

#include <vector>
#include <iostream>
#include "dao.h"

using namespace std;
using namespace db;

class UserDao final
{
public:
    UserDao();
    ~UserDao();
    
    bool GetByID(int id);
    bool GetByName(string name);
    vector<UserDao> Get(int offset, int limit);

    /**
         * 插入新的用户
         */
    bool Create();

    /**
         * 更新对应的用户
         */
    bool Update();

    


    inline void set_name(const string &name)
    {
        if ("" == name)
        {
            return;
        }

        this->m_name = name;
    }

    inline void set_pass(const string &pass)
    {
        if ("" == pass)
        {
            return;
        }

        this->m_pass = pass;
    }
    inline void set_last_login_time(const string &last_login_time)
    {
        if ("" == last_login_time)
        {
            return;
        }

        this->m_last_login_time = last_login_time;
    }
    inline void set_money(const int64_t money)
    {
        if (0 == money)
        {
            return;
        }

        this->m_money = money;
    }
    inline void set_groupid(const int32_t groupid)
    {
        if (0 == groupid)
        {
            return;
        }

        this->m_groupid = groupid;
    }

    inline int64_t id() const
    {
        return this->m_id;
    }


    inline string name() const
    {
        return this->m_name;
    }

    inline string pass() const
    {
        return this->m_pass;
    }
    inline string reg_time() const
    {
        return this->m_reg_time;
    }
    inline string last_login_time() const
    {
        return this->m_last_login_time;
    }
    inline int64_t money() const
    {
        return this->m_money;
    }
    inline int32_t group_id() const
    {
        return this->m_groupid;
    }

    string toString() const;
    friend ostream &operator<<(ostream &, const UserDao &);

private:
    // user表的信息
    int64_t m_id;
    string m_name;
    string m_pass;
    string m_reg_time;
    string m_last_login_time;
    int64_t m_money;
    int32_t m_groupid;
};

#endif