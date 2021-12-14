#include "tradedao.h"
#include "datetime.h"

TradeDao::TradeDao() : m_id(-1),
                       m_userid(-1),
                       m_goodid(-1),
                       m_trade_time(""),
                       m_trade_money(0),
                       m_trade_group_id(-1)
{
}

TradeDao::~TradeDao()
{
}

vector<TradeDao> TradeDao::Get(int userid)
{
    vector<TradeDao> trades;
    if (0 > userid)
    {
        return trades;
    }

    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return trades;
    }

    vector<map<string, Value>> temp = mysql->Selection("SELECT * FROM trade WHERE 玩家ID=" + to_string(userid));
    MysqlPool::Pool()->close(mysql);
    vector<map<string, Value>>::const_iterator it = temp.begin();
    while (it != temp.end())
    {
        map<string, Value> value = *it;
        map<string, Value>::const_iterator tit = value.begin();
        TradeDao trade;
        while (tit != value.end())
        {

            if ("订单ID" == tit->first)
            {
                trade.m_id = Value(tit->second).toInt();
            }
            if ("玩家ID" == tit->first)
            {
                trade.m_userid = Value(tit->second).toInt();
            }
            if ("道具ID" == tit->first)
            {
                trade.m_goodid = Value(tit->second).toInt();
            }
            if ("订单时间" == tit->first)
            {
                trade.m_trade_time = Value(tit->second).toString();
            }
            if ("交易金额" == tit->first)
            {
                trade.m_trade_money = Value(tit->second).toInt();
            }
            if ("订单类型" == tit->first)
            {
                trade.m_trade_group_id = Value(tit->second).toInt();
            }
            tit++;
        }
        trades.push_back(trade);

        it++;
    }

    return trades;
}

bool TradeDao::GetByID(int id)
{
    if (0 > id)
    {
        return false;
    }
    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return false;
    }
    vector<map<string, Value>> temp = mysql->Selection("SELECT * FROM trade WHERE 订单ID=" + to_string(id) + " limit 1");
    MysqlPool::Pool()->close(mysql);
    vector<map<string, Value>>::const_iterator it = temp.begin();
    if (it != temp.end())
    {
        map<string, Value> value = *it;
        map<string, Value>::const_iterator tit = value.begin();
        while (tit != value.end())
        {
            if ("订单ID" == tit->first)
            {
                this->m_id = Value(tit->second).toInt();
            }
            if ("玩家ID" == tit->first)
            {
                this->m_userid = Value(tit->second).toInt();
            }
            if ("道具ID" == tit->first)
            {
                this->m_goodid = Value(tit->second).toInt();
            }
            if ("订单时间" == tit->first)
            {
                this->m_trade_time = Value(tit->second).toString();
            }
            if ("交易金额" == tit->first)
            {
                this->m_trade_money = Value(tit->second).toInt();
            }
            if ("订单类型" == tit->first)
            {
                this->m_trade_group_id = Value(tit->second).toInt();
            }

            ++tit;
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool TradeDao::GetById(int goodid, int userid)
{
    if (0 == goodid || 0 == userid)
    {
        return false;
    }

    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return false;
    }

    vector<map<string, Value>> temp = mysql->Selection("SELECT * FROM trade WHERE 道具ID=" + to_string(goodid) + " AND 所属玩家ID=" + to_string(userid));
    MysqlPool::Pool()->close(mysql);
    vector<map<string, Value>>::const_iterator it = temp.begin();
    if (it != temp.end())
    {
        map<string, Value> value = *it;
        map<string, Value>::const_iterator tit = value.begin();
        while (tit != value.end())
        {
            if ("订单ID" == tit->first)
            {
                this->m_id = Value(tit->second).toInt();
            }
            if ("玩家ID" == tit->first)
            {
                this->m_userid = Value(tit->second).toInt();
            }
            if ("道具ID" == tit->first)
            {
                this->m_goodid = Value(tit->second).toInt();
            }
            if ("订单时间" == tit->first)
            {
                this->m_trade_time = Value(tit->second).toString();
            }
            if ("交易金额" == tit->first)
            {
                this->m_trade_money = Value(tit->second).toInt();
            }
            if ("订单类型" == tit->first)
            {
                this->m_trade_group_id = Value(tit->second).toInt();
            }

            ++tit;
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool TradeDao::Update()
{
    if (0 > this->m_id || 0 > this->m_userid || 0 > this->m_goodid)
    {
        return false;
    }

    bool isCan = false;
    string sql("UPDATE trade SET ");
    if ("" != this->m_trade_time)
    {
        isCan = true;
        sql += "订单时间='" + this->m_trade_time + "'";
    }

    if (0 != this->m_trade_money)
    {
        isCan = true;
        sql += ", 交易金额=" + to_string(this->m_trade_money) + "";
    }
    if (0 != this->m_trade_group_id)
    {
        isCan = true;
        sql += ", 订单类型=" + to_string(this->m_trade_group_id) + "";
    }
    if (!isCan)
    {
        return false;
    }

    stringstream stream;
    stream << this->m_id;
    ;
    string temp = stream.str();

    sql += " WHERE 订单ID=" + temp;
    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return false;
    }

    mysql->Exec(sql); // return  rows
    MysqlPool::Pool()->close(mysql);
    return true;
}

bool TradeDao::Create()
{
    if (0 > this->m_userid || 0 > this->m_goodid)
    {
        return false;
    }
    this->m_trade_time = Datetime::getCurrentDate();
    string sql("INSERT INTO trade(玩家ID,道具ID,订单时间,交易金额,订单类型) VALUE(");
    sql += to_string(this->m_userid) + ", ";
    sql += to_string(this->m_goodid) + ",'";
    sql += this->m_trade_time + "',";
    sql += to_string(this->m_trade_money) + ",";
    sql += to_string(this->m_trade_group_id) + ")";
    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return false;
    }
    //cout << sql << endl;
    mysql->Exec(sql);
    MysqlPool::Pool()->close(mysql);
    ; // return  rows
    this->GetByID(this->m_id);
    return true;
}

bool TradeDao::Delete()
{
    if (0 > this->m_id || 0 > this->m_userid)
    {
        return false;
    }
    string sql("DELETE FROM trade WHERE 订单ID=");
    sql += to_string(this->m_id) + " ";
    sql += "AND 玩家ID=";
    sql += to_string(this->m_userid) + " ";
    sql += "LIMIT 1";

    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return false;
    }

    mysql->Exec(sql);
    ; // return  rows
    MysqlPool::Pool()->close(mysql);
    return true;
}

string TradeDao::toString() const
{
    const string str = "订单ID: " + to_string(this->m_id) +
                       "\n所属用户ID: " + to_string(this->m_userid) +
                       "\n道具ID: " + to_string(this->m_goodid) +
                       "\n订单时间: " + this->m_trade_time +
                       "\n交易金额: " + to_string(this->m_trade_money);
    "\n订单类型: " + to_string(this->m_trade_group_id);

    return str;
}

ostream &operator<<(ostream &out, const TradeDao &trade)
{
    out << "m_id: " << trade.id();
    out << "\nm_uerid: " << trade.userid() << "\nm_goodid: " << trade.goodid();
    out << "\nm_trade_time: " << trade.trade_time() << "\nm_trade_money: " << trade.trade_money();
    out << "\ntrade_group_id: " << trade.trade_group_id() << endl;

    return out;
}
