# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库
add_library (MysqlDriver "${CMAKE_CURRENT_SOURCE_DIR}/mysqlDriver.cc")
target_link_libraries(MysqlDriver "${CMAKE_CURRENT_SOURCE_DIR}/mysql/lib/libmysqlclient.so")

# add_library (RedisDriver "${CMAKE_CURRENT_SOURCE_DIR}/redisDriver.cc")
# target_link_libraries(RedisDriver "${CMAKE_CURRENT_SOURCE_DIR}/libhiredis.so")

add_library (Mylib ${DIR_LIB_SRCS})
target_link_libraries(Mylib MysqlDriver "/usr/local/lib/libhiredis.so.0.13")
