#include "onsalegooddao.h"

OnSaleGoodDao::OnSaleGoodDao() : m_onsalegoodid(-1),
                                 m_name(""),
                                 m_userid(-1),
                                 m_price(-1),
                                 m_isSpecial(0),
                                 m_number(0),
                                 m_storeid(0)
{
}

OnSaleGoodDao::~OnSaleGoodDao()
{
}

vector<OnSaleGoodDao> OnSaleGoodDao::Get(int onsalegoodid)

{
    vector<OnSaleGoodDao> onsalegoods;
    if (0 > onsalegoodid)
    {
        return onsalegoods;
    }

    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return onsalegoods;
    }

    vector<map<string, Value>> temp = mysql->Selection("SELECT * FROM onSaleGood WHERE 道具ID=" + to_string(onsalegoodid));
    MysqlPool::Pool()->close(mysql);
    vector<map<string, Value>>::const_iterator it = temp.begin();
    while (it != temp.end())
    {
        map<string, Value> value = *it;
        map<string, Value>::const_iterator tit = value.begin();
        OnSaleGoodDao onsalegood;
        while (tit != value.end())
        {
            if ("道具ID" == tit->first)
            {
                onsalegood.m_onsalegoodid = Value(tit->second).toInt();
            }
            if ("道具名称" == tit->first)
            {
                onsalegood.m_name = Value(tit->second).toString();
            }
            if ("所属用户ID" == tit->first)
            {
                onsalegood.m_userid = Value(tit->second).toInt();
            }
            if ("售价" == tit->first)
            {
                onsalegood.m_price = Value(tit->second).toInt();
            }
            if ("道具属性" == tit->first)
            {
                onsalegood.m_isSpecial = Value(tit->second).toInt();
            }
            if ("数量" == tit->first)
            {
                this->m_number = Value(tit->second).toInt();
            }
            if ("商城ID" == tit->first)
            {
                this->m_storeid = Value(tit->second).toInt();
            }
            tit++;
        }
        onsalegoods.push_back(onsalegood);
        it++;
    }

    return onsalegoods;
}

vector<OnSaleGoodDao> OnSaleGoodDao::GetSpecial(int n) //获取n个SpecialGood

{
    vector<OnSaleGoodDao> onsalegoods;
    if (0 > n)
    {
        return onsalegoods;
    }

    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return onsalegoods;
    }

    vector<map<string, Value>> temp = mysql->Selection("SELECT * FROM onSaleGood where 道具属性=1 limit " + to_string(n));
    MysqlPool::Pool()->close(mysql);
    vector<map<string, Value>>::const_iterator it = temp.begin();
    while (it != temp.end())
    {
        map<string, Value> value = *it;
        map<string, Value>::const_iterator tit = value.begin();
        OnSaleGoodDao onsalegood;
        while (tit != value.end())
        {
            if ("道具ID" == tit->first)
            {
                onsalegood.m_onsalegoodid = Value(tit->second).toInt();
            }
            if ("道具名称" == tit->first)
            {
                onsalegood.m_name = Value(tit->second).toString();
            }
            if ("所属用户ID" == tit->first)
            {
                onsalegood.m_userid = Value(tit->second).toInt();
            }
            if ("售价" == tit->first)
            {
                onsalegood.m_price = Value(tit->second).toInt();
            }
            if ("道具属性" == tit->first)
            {
                onsalegood.m_isSpecial = Value(tit->second).toInt();
            }
            if ("数量" == tit->first)
            {
                this->m_number = Value(tit->second).toInt();
            }
            if ("商城ID" == tit->first)
            {
                this->m_storeid = Value(tit->second).toInt();
            }
            tit++;
        }
        onsalegoods.push_back(onsalegood);
        it++;
    }

    return onsalegoods;
}

bool OnSaleGoodDao::GetById(int userid, int onsalegoodid)
{
    if (0 == onsalegoodid)
    {
        return false;
    }

    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return false;
    }

    vector<map<string, Value>> temp = mysql->Selection("SELECT * FROM onSaleGood WHERE 道具ID=" + to_string(onsalegoodid) + " AND 所属用户ID=" + to_string(userid));
    MysqlPool::Pool()->close(mysql);
    vector<map<string, Value>>::const_iterator it = temp.begin();
    if (it != temp.end())
    {
        map<string, Value> value = *it;
        map<string, Value>::const_iterator tit = value.begin();
        while (tit != value.end())
        {
            if ("道具ID" == tit->first)
            {
                this->m_onsalegoodid = Value(tit->second).toInt();
            }
            if ("道具名称" == tit->first)
            {
                this->m_name = Value(tit->second).toString();
            }
            if ("所属用户ID" == tit->first)
            {
                this->m_userid = Value(tit->second).toInt();
            }
            if ("售价" == tit->first)
            {
                this->m_price = Value(tit->second).toInt();
            }
            if ("道具属性" == tit->first)
            {
                this->m_isSpecial = Value(tit->second).toInt();
            }
            if ("数量" == tit->first)
            {
                this->m_number = Value(tit->second).toInt();
            }
            if ("商城ID" == tit->first)
            {
                this->m_storeid = Value(tit->second).toInt();
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

bool OnSaleGoodDao::GetByName(string name)
{
    if ("" == name)
    {
        return false;
    }

    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return false;
    }

    vector<map<string, Value>> temp = mysql->Selection("SELECT * FROM onSaleGood WHERE 道具名称='" + name + "' limit 1");
    MysqlPool::Pool()->close(mysql);
    vector<map<string, Value>>::const_iterator it = temp.begin();
    if (it != temp.end())
    {
        map<string, Value> value = *it;
        map<string, Value>::const_iterator tit = value.begin();
        while (tit != value.end())
        {
            if ("道具ID" == tit->first)
            {
                this->m_onsalegoodid = Value(tit->second).toInt();
            }
            if ("道具名称" == tit->first)
            {
                this->m_name = Value(tit->second).toString();
            }
            if ("所属用户ID" == tit->first)
            {
                this->m_userid = Value(tit->second).toInt();
            }
            if ("售价" == tit->first)
            {
                this->m_price = Value(tit->second).toInt();
            }
            if ("道具属性" == tit->first)
            {
                this->m_isSpecial = Value(tit->second).toInt();
            }
            if ("数量" == tit->first)
            {
                this->m_number = Value(tit->second).toInt();
            }
            if ("商城ID" == tit->first)
            {
                this->m_storeid = Value(tit->second).toInt();
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

bool OnSaleGoodDao::Update()
{
    // 使用事务回滚以及悲观锁（排它锁），处理一致性问题
    if (0 > this->m_onsalegoodid)
    {
        return false;
    }

    bool isCan = false;
    string sql("UPDATE onSaleGood SET ");
    if (0 != this->m_number)
    {
        isCan = true;
        sql += "数量=" + to_string(this->m_number);
    }
    if (-1 != this->m_price)
    {
        isCan = true;
        sql += " , 售价=" + to_string(this->m_price);
    }

    if (!isCan)
    {
        return false;
    }
    stringstream stream;
    stream << this->m_onsalegoodid;
    ;
    string temp = stream.str();
    sql += " WHERE 道具ID=" + temp + " AND 所属用户ID=" + to_string(this->m_userid);
    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    string sqls("SELECT * FROM onSaleGood ");
    sqls += " WHERE 道具ID=" + temp + " AND 所属用户ID=" + to_string(this->m_userid);
    sqls += " FOR UPDATE";
    if (nullptr == mysql)
    {
        return false;
    }
    mysql->setAutoCommit(0);
    vector<map<string, Value>> res = mysql->Selection(sqls);
    if (res.size() == 0)
    {
        mysql->setAutoCommit(1);
        return false;
    }
    mysql->Exec(sql); // return  rows
    mysql->commit();
    mysql->setAutoCommit(1);
    MysqlPool::Pool()->close(mysql);
    return true;
}

bool OnSaleGoodDao::Create()
{
    if ("" == this->m_name || 0 > this->m_userid || 0 > this->m_onsalegoodid)
    {
        return false;
    }
    string sql("INSERT INTO onSaleGood(道具ID,道具名称,所属用户ID,售价,道具属性,数量) VALUE(");
    sql += to_string(this->m_onsalegoodid) + ",'";
    sql += this->m_name + "',";
    sql += to_string(this->m_userid) + ",";
    sql += to_string(this->m_price) + ",";
    sql += to_string(this->m_isSpecial) + ",";
    sql += to_string(this->m_number) + ")";

    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return false;
    }
    //cout << sql << endl;
    mysql->Exec(sql);
    MysqlPool::Pool()->close(mysql);
    ; // return  rows
    return true;
}

bool OnSaleGoodDao::Delete()
{   
    // 使用事务回滚以及悲观锁（排它锁），处理一致性问题
    if (0 > this->m_userid || 0 > this->m_onsalegoodid)
    {
        return false;
    }
    string sql("DELETE FROM onSaleGood WHERE 道具ID=");
    sql += to_string(this->m_onsalegoodid) + " ";
    sql += "AND 所属用户ID=";
    sql += to_string(this->m_userid) + " ";
    sql += "LIMIT 1";

    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    string sqls("SELECT * FROM onSaleGood ");
    sqls += " WHERE 道具ID=" + to_string(this->m_onsalegoodid) + " AND 所属用户ID=" + to_string(this->m_userid);
    sqls += " FOR UPDATE";
    if (nullptr == mysql)
    {
        return false;
    }
    mysql->setAutoCommit(0);
    vector<map<string, Value>> res = mysql->Selection(sqls);
    if (res.size() == 0)
    {
        mysql->setAutoCommit(1);
        return false;
    }
    mysql->Exec(sql); // return  rows
    mysql->commit();
    mysql->setAutoCommit(1);
    MysqlPool::Pool()->close(mysql);
    return true;
}

string OnSaleGoodDao::toString() const
{
    const string str = "在售道具Id: " + to_string(this->m_onsalegoodid) +
                       "\n在售道具名称: " + this->m_name +
                       "\n玩家id: " + to_string(this->m_userid) +
                       "\n价格: " + to_string(this->m_price) +
                       "\n道具属性: " + to_string(this->m_isSpecial) +
                       "\n商城ID: " + to_string(this->m_storeid);

    return str;
}

ostream &operator<<(ostream &out, const OnSaleGoodDao &onsalegood)
{
    out << "m_onsalegoodid: " << onsalegood.onsalegoodid();
    out << "\nm_name: " << onsalegood.name() << "\nm_userid: " << onsalegood.userid();
    out << "\nm_price: " << onsalegood.price() << endl;
    out << "\nm_isSpecial: " << onsalegood.isSpecial() << endl;
    out << "\nm_storeid: " << onsalegood.storeid() << endl;

    return out;
}
