#ifndef H_GOODDAO_H_
#define H_GOODDAO_H_

#include <vector>
#include <iostream>
#include "dao.h"

using namespace std;
using namespace db;

class GoodDao final
{
public:
    GoodDao();
    ~GoodDao();

    bool GetByName(string name);
    bool GetByID(int id);
    vector<GoodDao> Get(int offset, int limit);

    /**
         * 插入新的道具
         */
    bool Create();

    /**
         * 更新对应的道具
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

    inline void set_kind(const string &kind)
    {
        if ("" == kind)
        {
            return;
        }

        this->m_kind = kind;
    }
    inline void set_level(const int32_t level)
    {
        this->m_level = level;
    }
    inline void set_career(const string &career)
    {
        if ("" == career)
        {
            return;
        }

        this->m_career = career;
    }
    inline void set_grade(const int32_t grade)
    {
        this->m_grade = grade;
    }
    inline void set_color(const int32_t color)
    {
        this->m_color = color;
    }
    inline int64_t id() const
    {
        return this->m_id;
    }


    inline string name() const
    {
        return this->m_name;
    }

    inline string kind() const
    {
        return this->m_kind;
    }
    inline int32_t level() const
    {
        return this->m_level;
    }
    inline string career() const
    {
        return this->m_career;
    }
    inline int32_t grade() const
    {
        return this->m_grade;
    }
    inline int32_t color() const
    {
        return this->m_color;
    }


    string toString() const;
    friend ostream &operator<<(ostream &, const GoodDao &);

private:
    // good表的信息
    int64_t m_id;
    string m_name;
    string m_kind;
    int32_t m_level;
    string m_career;
    int32_t m_grade;
    int32_t m_color;
};

#endif