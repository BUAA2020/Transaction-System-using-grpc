#ifndef H_DATETIME_H_
#define H_DATETIME_H_

#ifdef _cplusplus
extern "C"
{
#endif
#include <time.h>
#include <sys/time.h>
#ifdef _cplusplus
}
#endif

#include <iostream>

using std::string;

class Datetime
{
public:
    // 获取当前的时间戳(秒级)
    static long getTimestamp(void);

    // 获取当前的时间戳（微秒级）

    static long getTimeustamp(void);

    // 获取当前的日期和时间, 格式：1900-01-01 00:00:01
    static string getCurrentDate(void);

    // 获取当前的日期和时间 ,格式：2017年 07月 16日 星期日 00:13:28 CST
    static string getCurrentDateForCST(void);

private:
};

#endif