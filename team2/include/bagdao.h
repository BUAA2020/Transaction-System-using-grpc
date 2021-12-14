#ifndef H_BAGDAO_H_
#define H_BAGDAO_H_

#include <vector>
#include <iostream>
#include "dao.h"

using namespace std;
using namespace db;

class BagDao final
{
public:
    BagDao();
    ~BagDao();

    bool GetById(int goodid,int userid);
    vector<BagDao> Get(int userid);

    /**
         * 插入新的背包道具道具
         */
    bool Create();

    /**
         * 更新对应的背包道具
         */
    bool Update();

    /**
         * 删除对应的背包道具
         */
    bool Delete();

    inline void set_userid(const int64_t userid)
    {
        this->m_userid = userid;
    }
    inline void set_goodid(const int64_t goodid)
    {
        this->m_goodid = goodid;
    }
    inline void set_name(const string &name)
    {
        if ("" == name)
        {
            return;
        }
        this->m_name = name;
    }

    inline void set_num(const int32_t num)
    {
        this->m_num = num;
    }
    inline int64_t goodid() const
    {
        return this->m_goodid;
    }
    inline int64_t userid() const
    {
        return this->m_userid;
    }

    inline string name() const
    {
        return this->m_name;
    }
    inline int32_t num() const
    {
        return this->m_num;
    }

    string toString() const;
    friend ostream &operator<<(ostream &, const BagDao &);

private:
    // bag表的信息
    int64_t m_goodid;
    string m_name;
    int64_t m_userid;
    int32_t m_num;
};

#endif