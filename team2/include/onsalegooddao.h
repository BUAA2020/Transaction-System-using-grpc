#ifndef H_ONSALEGOODDAO_H_
#define H_ONSALEGOODDAO_H_

#include <vector>
#include <iostream>
#include "dao.h"

using namespace std;
using namespace db;

class OnSaleGoodDao final
{
public:
    OnSaleGoodDao();
    ~OnSaleGoodDao();

    bool GetById(int userid,int onsalegoodid);
    bool GetByName(string name);
    vector<OnSaleGoodDao> Get(int onsalegoodid);
    vector<OnSaleGoodDao> GetSpecial(int n);
    /**
         * 插入新的在售商品道具
         */
    bool Create();

    /**
         * 更新对应的商品道具
         */
    bool Update();

    /**
         * 删除对应的商品道具
         */
    bool Delete();

    inline void set_userid(const int64_t userid)
    {
        this->m_userid = userid;
    }
    inline void set_onsalegoodid(const int64_t onsalegoodid)
    {
        this->m_onsalegoodid = onsalegoodid;
    }
    inline void set_name(const string &name)
    {
        if ("" == name)
        {
            return;
        }
        this->m_name = name;
    }
    inline void set_price(const int32_t price)
    {
        this->m_price = price;
    }

    inline void set_number(const int64_t number)
    {
        this->m_number = number;
    }

    inline void set_isSpecial(const int32_t isSpecial)
    {
        if (-1 == isSpecial)
        {
            return;
        }

        this->m_isSpecial = isSpecial;
    }

    inline void set_storeid(const int64_t storeid)
    {
        this->m_storeid = storeid;
    }

    inline int64_t onsalegoodid() const
    {
        return this->m_onsalegoodid;
    }
    inline int64_t userid() const
    {
        return this->m_userid;
    }

    inline string name() const
    {
        return this->m_name;
    }

    inline int32_t price() const
    {
        return this->m_price;
    }

    inline int32_t isSpecial() const
    {
        return this->m_isSpecial;
    }

    inline int64_t number() const
    {
        return this->m_number;
    }

    inline int64_t storeid() const
    {
        return this->m_storeid;
    }

    string toString() const;
    friend ostream &operator<<(ostream &, const OnSaleGoodDao &);

private:
    // OnSale道具表的信息
    int64_t m_onsalegoodid;
    string m_name;
    int64_t m_userid;
    int32_t m_price;
    int32_t m_isSpecial;
    int64_t m_number;
    int64_t m_storeid;
};

#endif