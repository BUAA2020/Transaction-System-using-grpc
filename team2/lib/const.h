#ifndef H_CONST_H_
#define H_CONST_H_

#include <map>
#include <iostream>

using namespace std;

namespace Const
{
    enum StatusCode
    {
        OK = 200,
        NAME_EMPTY = 2002,
        PASS_EMPTY = 2003,
        PASS_ERROR = 2004,
        ACCOUNT_EXIST = 2005,
        ACCOUNT_NOTEXIST = 2006,
        SIGNUP_FAILED = 2007,
        PERMISSION_DEFINED = 2008,
        BAG_FAILD = 2009,
        SERACH_FAILD = 2010,
        GOOD_NOTEXIST = 2011,
        ONSALE_FAILD = 2012,
        OFFSALE_FAILD = 2013,
        TRADE_EMPTY = 2014,
        MONEY_POOR = 2015,
        GOOD_POOR = 2016,
        KIND_MISTAKE = 2017,
        INPUT_ERROR = 2018,
        GOODSPECIAL_MISTAKE = 2019,
        SECKILL_FAILD = 3001,

    };

    map<StatusCode, string> StatusMsg{
        pair<StatusCode, string>(StatusCode::OK, "成功"),
        pair<StatusCode, string>(StatusCode::NAME_EMPTY, "名称为空"),
        pair<StatusCode, string>(StatusCode::PASS_EMPTY, "密码为空"),
        pair<StatusCode, string>(StatusCode::PASS_ERROR, "密码错误"),
        pair<StatusCode, string>(StatusCode::ACCOUNT_EXIST, "账号已经存在"),
        pair<StatusCode, string>(StatusCode::ACCOUNT_NOTEXIST, "账号不存在"),
        pair<StatusCode, string>(StatusCode::SIGNUP_FAILED, "注册失败"),
        pair<StatusCode, string>(StatusCode::PERMISSION_DEFINED, "无此权限"),
        pair<StatusCode, string>(StatusCode::BAG_FAILD, "背包出错"),
        pair<StatusCode, string>(StatusCode::SERACH_FAILD, "查询失败"),
        pair<StatusCode, string>(StatusCode::GOOD_NOTEXIST, "道具不存在"),
        pair<StatusCode, string>(StatusCode::ONSALE_FAILD, "上架道具失败"),
        pair<StatusCode, string>(StatusCode::OFFSALE_FAILD, "下架道具失败"),
        pair<StatusCode, string>(StatusCode::TRADE_EMPTY, "交易不存在"),
        pair<StatusCode, string>(StatusCode::MONEY_POOR, "金币不足"),
        pair<StatusCode, string>(StatusCode::GOOD_POOR, "道具不足"),
        pair<StatusCode, string>(StatusCode::KIND_MISTAKE, "操作类型错误"),
        pair<StatusCode, string>(StatusCode::INPUT_ERROR, "非法输入"),
        pair<StatusCode, string>(StatusCode::GOODSPECIAL_MISTAKE, "道具类型错误"),
        pair<StatusCode, string>(StatusCode::SECKILL_FAILD, "秒杀失败"),

    };

    string GetStatusMsg(StatusCode code)
    {
        map<StatusCode, string>::iterator it = StatusMsg.find(code);
        if (it == StatusMsg.end())
        {
            return "异常错误";
        }

        return it->second;
    }
};

#endif