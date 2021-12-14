#ifndef H_TRADE_H_
#define H_TRADE_H_

#include <vector>
#include <iostream>
#include "dao.h"

using namespace std;
using namespace db;

class TradeDao final
{
public:
    TradeDao();
    ~TradeDao();
    
    bool GetByID(int id);
    bool GetById(int goodid,int userid);


    vector<TradeDao> Get(int userid);
  /**
         * 插入新的订单
         */
    bool Create();

    /**
         * 更新对应的订单
         */
    bool Update();

     /**
         * 删除对应的订单
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

    
    inline void set_trade_time(const string &trade_time)
    {
        if ("" == trade_time)
        {
            return;
        }

        this->m_trade_time = trade_time;
    }
    inline void set_trade_money(const int64_t trade_money)
    {
        if (0 == trade_money)
        {
            return;
        }

        this->m_trade_money = trade_money;
    }
    inline void set_trade_group_id(const int32_t trade_group_id)
    {
        if (0 == trade_group_id)
        {
            return;
        }

        this->m_trade_group_id = trade_group_id;
    }

    inline int64_t id() const
    {
        return this->m_id;
    }

   
    inline int64_t userid() const
    {
        return this->m_userid;
    } 
     inline int64_t goodid() const
    {
        return this->m_goodid;
    }
   
    
    inline string trade_time() const
    {
        return this->m_trade_time;
    }
    inline int64_t trade_money() const
    {
        return this->m_trade_money;
    }
    inline int32_t trade_group_id() const
    {
        return this->m_trade_group_id;
    }

    string toString() const;
    friend ostream &operator<<(ostream &, const TradeDao &);

private:
    // trade表的信息
    int64_t m_id;
    int64_t m_userid;
    int64_t m_goodid;
    string m_trade_time;
    int64_t m_trade_money;
    int32_t m_trade_group_id;
};

#endif