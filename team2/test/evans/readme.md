# 说明

本工具用于对接口进行单元测试，通过返回值验证接口正确性

# 使用说明

分两种模式

## REPL mode


通过下命令开始，ip、port和proto可以换
```shell
 ./evans  --host=localhost --port=50051 ./basicInfoService.proto
```

之后进入到REPL模式界面


以下命令显示proto文件中的命名空间
```shell
show package
```

以下命令表示使用该package
```shell
package myApplication
```

以下命令显示命名空间中的服务及其接口信息
```shell
show service
```

以下命令显示其中的message信息
```shell
show message
```

表示使用该服务，建议对此服务的客户端
```shell
service BasicInfoService
```

以下命令发送对某个接口的请求，xxx可以是doLogin等
```shell
call xxxx
```

### 小窍门

该模式提供自动补全，使用tab可以切换

## CLI mode

基本使用：
```shell
 ./evans  --proto ./basicInfoService.proto --host localhost --port 50051 cli [options]
```

### list

显示proto文件中的命名空间和服务名称

### call

对指定接口进行请求，需要给定json文件
```shell
 ./evans  --proto ./basicInfoService.proto --host localhost --port 50051 cli  call --file logintest.json myApplication.BasicInfoService.doLogin
```


# 单元测试脚本说明

新建一个管理员用户
```shell
 ./evans  --proto ./basicInfoService.proto --host localhost --port 50051 cli  call --file registertest.json myApplication.BasicInfoService.doRegister
```

登录用户
```shell
 ./evans  --proto ./basicInfoService.proto --host localhost --port 50051 cli  call --file logintest.json myApplication.BasicInfoService.doLogin
```

查询用户拥有的道具及名称
```shell
 ./evans  --proto ./basicInfoService.proto --host localhost --port 50051 cli  call --file searchusertest.json myApplication.BasicInfoService.doSearchUserInfo
```

更改用户密码及金币
```shell
 ./evans  --proto ./basicInfoService.proto --host localhost --port 50051 cli  call --file modifyuser.json myApplication.BasicInfoService.doModifyUserInfo
```

根据id查询道具信息
```shell
 ./evans  --proto ./basicInfoService.proto --host localhost --port 50051 cli  call --file searchgoodtest.json myApplication.BasicInfoService.doSearchGoodInfo
```

修改道具信息
```shell
 ./evans  --proto ./basicInfoService.proto --host localhost --port 50051 cli  call --file modifygood.json myApplication.BasicInfoService.doModifyGoodInfo
```

玩家上架道具
```shell
 ./evans  --proto ./MallService.proto --host localhost --port 50051 cli  call --file saletest.json myApplication.MallService.doSale
```

玩家下架道具
```shell
 ./evans  --proto ./MallService.proto --host localhost --port 50051 cli  call --file upsale.json myApplication.MallService.doSale
```

查询商场在售道具
```shell
 ./evans  --proto ./MallService.proto --host localhost --port 50051 cli  call --file searchonsale.json myApplication.MallService.doSearchOnSaleGoods
```

购买道具
```shell
./evans  --proto ./MallService.proto --host localhost --port 50051 cli  call --file purchase.json myApplication.MallService.doPurchase
```

查询指定用户交易记录
```shell
./evans  --proto ./MallService.proto --host localhost --port 50051 cli  call --file tradetest.json myApplication.MallService.doManageTrades
```

