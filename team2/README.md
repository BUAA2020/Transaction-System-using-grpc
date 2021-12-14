# 目录树

共计 26 directories, 209 files



```txt
.
|-- client              # 一个客户端
|   `-- protos  
|-- conf                # 配置文件
|-- include             # 头文件
|-- lib                 # 依赖的第三方库以及自己编写的一些工具
|   |-- cmake
|   |-- hiredis
|   |-- mysql
|-- myDB                # 生成mysql的脚本
|-- picture             # 项目的类图时序图
|-- src                 # 源文件
|   |-- basicInfoServer # 基本信息服务
|   |   `-- protos
|   |-- mallServer      # 商场服务
|   |   `-- protos
|   `-- seckillServer   # 秒杀服务
|       `-- protos
`-- test                # 测试工具及脚本
```


## lib

存放项目依赖的库文件及其实现，所有服务公用


## include

存放项目头文件

## src

存放源代码


### basicInfoServer

存放基本服务的服务端源码以及协议文件

### mallServer

存放商场服务的服务端代码以及协议文件

### seckillServer

存放秒杀服务的服务端代码以及协议文件

## myDB

存放数据库初始化的sql脚本，以及初始化导入的数据

## conf

存放配置文件


# 程序的编译

```shell
mkdir build
cmake ..
make
```

# 服务的运行

编译后生成的可执行文件在根目录下，直接运行即可

# 第三方库

mysql-connection

hiredis
> hiredis在lib文件夹中，进入后，make,make install

# 环境

Linux

protobuf    3.18

gprc        1.42

cmake       3.21

gcc         8.3

# 数据库初始化脚本

位于myDB目录下的init.sql。进入该目录，连接mysql，执行`source init.sql`即可。

如果连接mysql报错：
```shell
 InitConnection : Error connection to database:Can't connect to local MySQL server through socket '/tmp/mysql.sock' (2)
```

则执行下：

```shell
ln -s /var/lib/mysql/mysql.sock /tmp/mysql.sock
```