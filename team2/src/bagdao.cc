#include "bagdao.h"

BagDao::BagDao() : m_userid(-1),
                   m_name(""),
                   m_num(0),
                   m_goodid(-1)
{
}

BagDao::~BagDao()
{
}

vector<BagDao> BagDao::Get(int userid)
{
    vector<BagDao> bags;
    if (0 > userid)
    {
        return bags;
    }

    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return bags;
    }

    vector<map<string, Value>> temp = mysql->Selection("SELECT * FROM bag WHERE 所属玩家ID=" + to_string(userid));
    MysqlPool::Pool()->close(mysql);
    vector<map<string, Value>>::const_iterator it = temp.begin();
    while (it != temp.end())
    {
        map<string, Value> value = *it;
        map<string, Value>::const_iterator tit = value.begin();
        BagDao bag;
        while (tit != value.end())
        {
            if ("道具ID" == tit->first)
            {
                bag.m_goodid = Value(tit->second).toInt();
            }
            if ("道具名称" == tit->first)
            {
                bag.m_name = Value(tit->second).toString();
            }
            if ("数量" == tit->first)
            {
                bag.m_num = Value(tit->second).toInt();
            }
            if ("所属玩家ID" == tit->first)
            {
                bag.m_userid = Value(tit->second).toInt();
            }
            tit++;
        }
        bags.push_back(bag);
        it++;
    }

    return bags;
}

bool BagDao::GetById(int goodid, int userid)
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

    vector<map<string, Value>> temp = mysql->Selection("SELECT * FROM bag WHERE 道具ID=" + to_string(goodid) + " AND 所属玩家ID=" + to_string(userid));
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
                this->m_goodid = Value(tit->second).toInt();
            }
            if ("道具名称" == tit->first)
            {
                this->m_name = Value(tit->second).toString();
            }
            if ("所属玩家ID" == tit->first)
            {
                this->m_userid = Value(tit->second).toInt();
            }
            if ("数量" == tit->first)
            {
                this->m_num = Value(tit->second).toInt();
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

bool BagDao::Update()
{
    if (0 > this->m_userid || 0 > this->m_goodid)
    {
        return false;
    }

    bool isCan = false;
    string sql("UPDATE bag SET ");
    if (0 != this->m_num)
    {
        isCan = true;
        sql += "数量=" + to_string(this->m_num);
    }
    if (!isCan)
    {
        return false;
    }

    stringstream stream;
    stream << this->m_goodid;
    ;
    string temp = stream.str();
    sql += " WHERE 道具ID=" + temp + " AND 所属玩家ID=" + to_string(this->m_userid);

    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return false;
    }
    mysql->Exec(sql); // return  rows
    MysqlPool::Pool()->close(mysql);
    return true;
}

bool BagDao::Create()
{
    if ("" == this->m_name || 0 > this->m_userid || 0 > this->m_goodid)
    {
        return false;
    }
    string sql("INSERT INTO bag(道具ID,道具名称,所属玩家ID,数量) VALUE(");
    sql += to_string(this->m_goodid) + ",'";
    sql += this->m_name + "',";
    sql += to_string(this->m_userid) + ",";
    sql += to_string(this->m_num) + ")";

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

bool BagDao::Delete()
{
    if (0 > this->m_userid || 0 > this->m_goodid)
    {
        return false;
    }
    string sql("DELETE FROM bag WHERE 道具ID=");
    sql += to_string(this->m_goodid) + " ";
    sql += "AND 所属玩家ID=";
    sql += to_string(this->m_userid) + " ";
    sql += "LIMIT 1";

    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return false;
    }
    mysql->Exec(sql);
    MysqlPool::Pool()->close(mysql);
    ; // return  rows
    return true;
}

string BagDao::toString() const
{
    const string str = "道具Id: " + to_string(this->m_goodid) +
                       "\n道具名称: " + this->m_name +
                       "\n所属玩家ID: " + to_string(this->m_userid) +
                       "\n数量: " + to_string(this->m_num);

    return str;
}

ostream &operator<<(ostream &out, const BagDao &bag)
{
    out << "m_goodid: " << bag.goodid();
    out << "\nm_name: " << bag.name() << "\nm_userid: " << bag.userid();
    out << "\nm_num: " << bag.num() << endl;

    return out;
}
