#include "userdao.h"
#include "datetime.h"

UserDao::UserDao() : m_id(-1),
                     m_name(""),
                     m_pass(""),
                     m_reg_time(""),
                     m_last_login_time(""),
                     m_money(0),
                     m_groupid(-1)
{
}

UserDao::~UserDao()
{
}

vector<UserDao> UserDao::Get(int offset, int limit)
{
    vector<UserDao> users;
    if (0 > offset || 0 > limit)
    {
        return users;
    }

    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return users;
    }

    vector<map<string, Value>> temp = mysql->Selection("SELECT * FROM user WHERE id=" + to_string(offset) + " limit " + to_string(limit));
    MysqlPool::Pool()->close(mysql);
    vector<map<string, Value>>::const_iterator it = temp.begin();
    while (it != temp.end())
    {
        map<string, Value> value = *it;
        map<string, Value>::const_iterator tit = value.begin();
        UserDao user;
        while (tit != value.end())
        {

            if ("id" == tit->first)
            {
                user.m_id = Value(tit->second).toInt();
            }
            if ("name" == tit->first)
            {
                user.m_name = Value(tit->second).toString();
            }
            if ("pass" == tit->first)
            {
                user.m_pass = Value(tit->second).toString();
            }
            if ("last_login_time" == tit->first)
            {
                user.m_last_login_time = Value(tit->second).toString();
            }
            if ("reg_time" == tit->first)
            {
                user.m_reg_time = Value(tit->second).toString();
            }
            if ("money" == tit->first)
            {
                user.m_money = Value(tit->second).toInt();
            }
            if ("groupid" == tit->first)
            {
                user.m_groupid = Value(tit->second).toInt();
            }
            tit++;
        }
        users.push_back(user);

        it++;
    }

    return users;
}

bool UserDao::GetByID(int id)
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
    vector<map<string, Value>> temp = mysql->Selection("SELECT * FROM user WHERE id=" + to_string(id) + " limit 1");
    MysqlPool::Pool()->close(mysql);
    vector<map<string, Value>>::const_iterator it = temp.begin();
    if (it != temp.end())
    {
        map<string, Value> value = *it;
        map<string, Value>::const_iterator tit = value.begin();
        while (tit != value.end())
        {
            if ("id" == tit->first)
            {
                this->m_id = Value(tit->second).toInt();
            }
            if ("name" == tit->first)
            {
                this->m_name = Value(tit->second).toString();
            }
            if ("pass" == tit->first)
            {
                this->m_pass = Value(tit->second).toString();
            }
            if ("last_login_time" == tit->first)
            {
                this->m_last_login_time = Value(tit->second).toString();
            }
            if ("reg_time" == tit->first)
            {
                this->m_reg_time = Value(tit->second).toString();
            }
            if ("money" == tit->first)
            {
                this->m_money = Value(tit->second).toInt();
            }
            if ("groupid" == tit->first)
            {
                this->m_groupid = Value(tit->second).toInt();
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

bool UserDao::GetByName(string name)
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

    vector<map<string, Value>> temp = mysql->Selection("SELECT * FROM user WHERE name='" + name + "' limit 1");
    MysqlPool::Pool()->close(mysql);
    vector<map<string, Value>>::const_iterator it = temp.begin();
    if (it != temp.end())
    {
        map<string, Value> value = *it;
        map<string, Value>::const_iterator tit = value.begin();
        while (tit != value.end())
        {
            if ("id" == tit->first)
            {
                this->m_id = Value(tit->second).toInt();
            }
            if ("name" == tit->first)
            {
                this->m_name = Value(tit->second).toString();
            }
            if ("pass" == tit->first)
            {
                this->m_pass = Value(tit->second).toString();
            }
            if ("last_login_time" == tit->first)
            {
                this->m_last_login_time = Value(tit->second).toString();
            }
            if ("reg_time" == tit->first)
            {
                this->m_reg_time = Value(tit->second).toString();
            }
            if ("money" == tit->first)
            {
                this->m_money = Value(tit->second).toInt();
            }
            if ("groupid" == tit->first)
            {
                this->m_groupid = Value(tit->second).toInt();
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

bool UserDao::Update()
{
    if (0 > this->m_id)
    {
        return false;
    }

    bool isCan = false;
    string sql("UPDATE user SET ");
    if ("" != this->m_pass)
    {
        isCan = true;
        sql += "pass='" + this->m_pass + "'";
    }

    if ("" != this->m_reg_time)
    {
        isCan = true;
        sql += ", reg_time='" + this->m_reg_time + "'";
    }
    if ("" != this->m_last_login_time)
    {
        isCan = true;
        sql += ", last_login_time='" + this->m_last_login_time + "'";
    }
    if (0 <= this->m_money)
    {
        isCan = true;
        sql += ", money= " + to_string(this->m_money);
    }
    if (!isCan)
    {
        return false;
    }

    stringstream stream;
    stream << this->m_id;
    ;
    string temp = stream.str();

    sql += " WHERE id=" + temp;
    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return false;
    }

    mysql->Exec(sql); // return  rows
    MysqlPool::Pool()->close(mysql);
    return true;
}

bool UserDao::Create()
{
    if ("" == this->m_name)
    {
        return false;
    }
    this->m_reg_time = Datetime::getCurrentDate();
    this->m_money = 100;
    string sql("INSERT INTO user(name,pass,last_login_time,reg_time,money,groupid) VALUE('");
    sql += this->m_name + "','";
    sql += this->m_pass + "','";
    sql += this->m_last_login_time + "','";
    sql += this->m_reg_time + "',";
    sql += to_string(this->m_money) + ",";
    sql += to_string(this->m_groupid) + ")";
    shared_ptr<MysqlUtil> mysql = MysqlPool::Pool()->mysql();
    if (nullptr == mysql)
    {
        return false;
    }
    //cout << sql << endl;
    mysql->Exec(sql);

    ; // return  rows
    MysqlPool::Pool()->close(mysql);
    this->GetByName(this->m_name);
    return true;
}

string UserDao::toString() const
{
    const string str = "Id: " + to_string(this->m_id) +
                       "\nName: " + this->m_name +
                       "\nPassword: " + this->m_pass +
                       "\nlast_login_time: " + this->m_last_login_time +
                       "\nreg_time: " + this->m_reg_time +
                       "\nMoney: " + to_string(this->m_money);
    "\nGroupID: " + to_string(this->m_groupid);

    return str;
}

ostream &operator<<(ostream &out, const UserDao &user)
{
    out << "m_id: " << user.id();
    out << "\nm_last_login_time: " << user.last_login_time() << "\nm_name: " << user.name();
    out << "\nm_pass: " << user.pass() << "\nm_reg_time: " << user.reg_time();
    out << "\nMoney: " << user.money() << "\nGroupID: " << user.group_id() << endl;

    return out;
}
