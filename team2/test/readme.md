# gprc测试

我们测试使用 ghz 第三方工具，专门用来对gprc服务进行负载测试和压力测试

## 运行

在本文件中，ghz程序是直接用来执行的

config.json是执行此程序的配置文件

```json
{
  "call": "myApplication.BasicInfoService.doLogin",  // 测试的服务接口
  "host": "127.0.0.1:50051",                   // 测试的端口
  "proto": "./basicInfoService.proto",          // 测试的proto文件
  "insecure": true,
  "load-schedule": "const",                     // 负载测试的策略，以RPS=CONST 的速率发送请求，默认没有限制
  "rps": "1000",                                // 每秒1000个请求
  "concurrency": 50,                            // 并发数50
  "concurrency-schedule": "const",              // 模拟并发数的策略
  "total": 5000,                                // 总共发送5000个请求
  "connections": 1,                             // 链接数
  "data": {                                     // 请求的数据体
    "passWord": "123456",
    "userName": "kxz"
  },
  "debug" : "./debug.json",                     // 输出每个rpc请求的响应信息，用于debug
  "output": "./result.json",                    // 测试结果存储路径
  "format": "json"                              // summary, csv, json, pretty, html, influx-summary, influx-details. Default is summary，html会有可视化图表
}
```

在Shell命令行执行下即可运行：

```shell
./ghz --config=./config.json
```

# 用于测试的数据

下面列出一些可用于测试的json包
## myApplication

在ghz中使用测试的json

### BasicInfoService

#### doLogin

##### 一个账户登陆的json

```json
{
  "userName": "Hello",
  "passWord": "Hello"
}
```

#### doRegister

##### 注册一个用户

```json
{
  "userName": "zzz",
  "passWord": "111111",
  "groupid": 2
}
```

##### 注册十个用户

```json
{
  "userName": "{{randomString 3 }}",
  "passWord": "123456",
  "groupid": 1
}
```

配置文件中

```json                             
    "total": 10                              
```

#### doModifyUserInfo

##### 修改用户密码

```json
{
  "userName": "grpc",
  "passWord": "111111"
}
```

#### doSearchUserInfo

##### 查询用户信息

这里并发100，发送10000个包，测试负载和压力

```json
{
  "id": 7
}
```

配置文件里

```json
    "concurrency": 100,                        
    "total": 10000, 
```

#### doModifyGoodInfo

##### 修改道具信息

除了道具名称必选，其他选择一个修改即可

```json
{
  "goodName": "北斗石",
  "kind": "宝石",
  "level": 10,
  "career": "不限",
  "grade": 1,
  "color": 2
}
```

#### doSearchGoodInfo

##### 除查找指定id道具

```json
{
  "id": 666
}
```

也可设置并发量来进行压测

### MallService

#### doSale

##### 上架道具

```json
{
  "goodid": 1188,
  "money": 20,
  "id": 14,
  "kind": 2,
  "num": 1,
  "goodSpecial": 0
}
```

#### doPurchase

并发一致性测试

```json
{
  "goodid": 672,
  "money": 10,
  "id": "{{randomInt 3 13}}",
  "num": 1,
  "goodSpecial": 0,
  "salerid": 2
}
```