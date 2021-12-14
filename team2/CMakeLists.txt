cmake_minimum_required(VERSION 3.5.1)
project(Service C CXX)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}) 


include(./common.cmake)
include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/lib")
include_directories("${CMAKE_SOURCE_DIR}/lib/hiredis")
include_directories("${CMAKE_SOURCE_DIR}/lib/mysql/include")

add_subdirectory("${CMAKE_SOURCE_DIR}/src/mallServer")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/basicInfoServer")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/seckillServer")
add_subdirectory(lib)

aux_source_directory("${CMAKE_SOURCE_DIR}/src/" DAO_SRCS)

  
# Targets greeter_[async_](client|server)
add_executable(basicInfo "src/basicInfoServer/basicInfoServer.cc" "${DAO_SRCS}")
target_link_libraries(basicInfo
basic_grpc_proto
Mylib
${_REFLECTION}
${_GRPC_GRPCPP}
${_PROTOBUF_LIBPROTOBUF})

add_executable(mall "src/mallServer/mallServer.cc" "${DAO_SRCS}")
target_link_libraries(mall
mall_grpc_proto
Mylib
${_REFLECTION}
${_GRPC_GRPCPP}
${_PROTOBUF_LIBPROTOBUF})

add_executable(seckill "src/seckillServer/seckillServer.cc" "src/seckillServer/Worker.cc" "src/seckillServer/Md5.cc" "${DAO_SRCS}")
target_link_libraries(seckill
seckill_grpc_proto
Mylib
${_REFLECTION}
${_GRPC_GRPCPP}
${_PROTOBUF_LIBPROTOBUF})

