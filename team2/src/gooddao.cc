#include "gooddao.h"
#include "datetime.h"

GoodDao::GoodDao() : m_id(-1),
                     m_name(""),
                     m_kind(""),
                     m_level(0),
                     m_career(""),
                     m_grade(0),
                     m_color(0)

{
}

GoodDao::~GoodDao()
{
}

vector<GoodDao> GoodDao::Get(int offset, int limit)
{
    vector<GoodDao> goods;
    if (0 > offset || 0 > limit)
    {
        return goods;
    }

    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return goods;
    }

    vector<map<string, Value>> temp = mysql->Selection("SELECT * FROM good WHERE 道具ID=" + to_string(offset) + " limit " + to_string(limit));
    MysqlPool::Pool()->close(mysql);
    vector<map<string, Value>>::const_iterator it = temp.begin();
    while (it != temp.end())
    {
        map<string, Value> value = *it;
        map<string, Value>::const_iterator tit = value.begin();
        GoodDao good;
        while (tit != value.end())
        {

            if ("道具ID" == tit->first)
            {
                good.m_id = Value(tit->second).toInt();
            }
            if ("道具名称" == tit->first)
            {
                good.m_name = Value(tit->second).toString();
            }
            if ("道具类别" == tit->first)
            {
                good.m_kind = Value(tit->second).toString();
            }
            if ("最低使用等级" == tit->first)
            {
                good.m_level = Value(tit->second).toInt();
            }
            if ("适用职业" == tit->first)
            {
                good.m_career = Value(tit->second).toString();
            }
            if ("物品档次" == tit->first)
            {
                good.m_grade = Value(tit->second).toInt();
            }
            if ("物品颜色" == tit->first)
            {
                good.m_color = Value(tit->second).toInt();
            }

            tit++;
        }
        goods.push_back(good);
        it++;
    }

    return goods;
}

bool GoodDao::GetByName(string name)
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

    vector<map<string, Value>> temp = mysql->Selection("SELECT * FROM good WHERE 道具名称='" + name + "' limit 1");
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
                this->m_id = Value(tit->second).toInt();
            }
            if ("道具名称" == tit->first)
            {
                this->m_name = Value(tit->second).toString();
            }
            if ("道具类别" == tit->first)
            {
                this->m_kind = Value(tit->second).toString();
            }
            if ("最低使用等级" == tit->first)
            {
                this->m_level = Value(tit->second).toInt();
            }
            if ("适用职业" == tit->first)
            {
                this->m_career = Value(tit->second).toString();
            }
            if ("物品档次" == tit->first)
            {
                this->m_grade = Value(tit->second).toInt();
            }
            if ("物品颜色" == tit->first)
            {
                this->m_color = Value(tit->second).toInt();
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

bool GoodDao::GetByID(int id)
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

    vector<map<string, Value>> temp = mysql->Selection("SELECT * FROM good WHERE 道具ID=" + to_string(id) + " limit 1");
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
                this->m_id = Value(tit->second).toInt();
            }
            if ("道具名称" == tit->first)
            {
                this->m_name = Value(tit->second).toString();
            }
            if ("道具类别" == tit->first)
            {
                this->m_kind = Value(tit->second).toString();
            }
            if ("最低使用等级" == tit->first)
            {
                this->m_level = Value(tit->second).toInt();
            }
            if ("适用职业" == tit->first)
            {
                this->m_career = Value(tit->second).toString();
            }
            if ("物品档次" == tit->first)
            {
                this->m_grade = Value(tit->second).toInt();
            }
            if ("物品颜色" == tit->first)
            {
                this->m_color = Value(tit->second).toInt();
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

bool GoodDao::Update()
{
    if (0 > this->m_id)
    {
        return false;
    }

    bool isCan = false;
    string sql("UPDATE good SET ");
    if ("" != this->m_name)
    {
        isCan = true;
        sql += "道具名称='" + this->m_name + "'";
    }

    if ("" != this->m_kind)
    {
        isCan = true;
        sql += ", 道具类别='" + this->m_kind + "'";
    }
    if (0 != this->m_level)
    {
        isCan = true;
        sql += ", 最低使用等级=" + to_string(this->m_level);
    }
    if ("" != this->m_career)
    {
        isCan = true;
        sql += ", 适用职业='" + this->m_career + "'";
    }
    if (0 != this->m_grade)
    {
        isCan = true;
        sql += ", 物品档次=" + to_string(this->m_grade);
    }
    if (0 != this->m_color)
    {
        isCan = true;
        sql += ", 物品颜色=" + to_string(this->m_color);
    }
    if (!isCan)
    {
        return false;
    }

    stringstream stream;
    stream << this->m_id;
    ;
    string temp = stream.str();

    sql += " WHERE 道具ID=" + temp;
    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return false;
    }

    mysql->Exec(sql); // return  rows
    MysqlPool::Pool()->close(mysql);
    return true;
}

bool GoodDao::Create()
{
    if ("" == this->m_name)
    {
        return false;
    }
    string sql("INSERT INTO good(道具名称,道具类别,最低使用等级,适用职业,物品档次,物品颜色) VALUE('");
    sql += this->m_name + "','";
    sql += this->m_kind + "',";
    sql += to_string(this->m_level) + ",'";
    sql += this->m_career + "',";
    sql += to_string(this->m_grade) + ",";
    sql += to_string(this->m_color) + ")";

    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return false;
    }
    //cout << sql << endl;
    mysql->Exec(sql);
    MysqlPool::Pool()->close(mysql);
    ; // return  rows
    this->GetByName(this->m_name);
    return true;
}

string GoodDao::toString() const
{
    const string str = "道具Id: " + to_string(this->m_id) +
                       "\n道具名称: " + this->m_name +
                       "\n道具类别: " + this->m_kind +
                       "\n最低使用等级: " + to_string(this->m_level) +
                       "\n适用职业: " + this->m_career +
                       "\n物品档次: " + to_string(this->m_grade) +
                       "\n物品颜色: " + to_string(this->m_color);

    return str;
}

ostream &operator<<(ostream &out, const GoodDao &good)
{
    out << "m_id: " << good.id();
    out << "\nm_name: " << good.name() << "\nm_kind: " << good.kind();
    out << "\nm_level: " << good.level() << "\nm_career: " << good.career();
    out << "\nm_grade: " << good.grade() << "\nm_color: " << good.color() << endl;

    return out;
}
