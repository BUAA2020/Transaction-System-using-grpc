cmake_minimum_required(VERSION 3.5.1)
project(Client C CXX)

include(../common.cmake)
include_directories("${CMAKE_SOURCE_DIR}/../include")
include_directories("${CMAKE_SOURCE_DIR}/../lib")
add_subdirectory(../lib Mylib.out)



# Proto file
get_filename_component(basic_proto "${CMAKE_CURRENT_SOURCE_DIR}/protos/basicInfoService.proto" ABSOLUTE)
get_filename_component(basic_proto_path "${basic_proto}" PATH)

# Generated sources
set(basic_proto_srcs "${CMAKE_CURRENT_SOURCE_DIR}/protos/basicInfoService.pb.cc")
set(basic_proto_hdrs "${CMAKE_CURRENT_SOURCE_DIR}/protos/basicInfoService.pb.h")
set(basic_grpc_srcs "${CMAKE_CURRENT_SOURCE_DIR}/protos/basicInfoService.grpc.pb.cc")
set(basic_grpc_hdrs "${CMAKE_CURRENT_SOURCE_DIR}/protos/basicInfoService.grpc.pb.h")
add_custom_command(
      OUTPUT "${basic_proto_srcs}" "${basic_proto_hdrs}" "${basic_grpc_srcs}" "${basic_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_SOURCE_DIR}/protos"
        --cpp_out "${CMAKE_CURRENT_SOURCE_DIR}/protos"
        -I "${basic_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${basic_proto}"
      DEPENDS "${basic_proto}")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/protos")

# grpc_proto
add_library(basic_grpc_proto
  ${basic_grpc_srcs}
  ${basic_grpc_hdrs}
  ${basic_proto_srcs}
  ${basic_proto_hdrs})
target_link_libraries(basic_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})


  # Proto file
get_filename_component(mall_proto "${CMAKE_CURRENT_SOURCE_DIR}/protos/MallService.proto" ABSOLUTE)
get_filename_component(mall_proto_path "${mall_proto}" PATH)

# Generated sources
set(mall_proto_srcs "${CMAKE_CURRENT_SOURCE_DIR}/protos/MallService.pb.cc")
set(mall_proto_hdrs "${CMAKE_CURRENT_SOURCE_DIR}/protos/MallService.pb.h")
set(mall_grpc_srcs "${CMAKE_CURRENT_SOURCE_DIR}/protos/MallService.grpc.pb.cc")
set(mall_grpc_hdrs "${CMAKE_CURRENT_SOURCE_DIR}/protos/MallService.grpc.pb.h")
add_custom_command(
      OUTPUT "${mall_proto_srcs}" "${mall_proto_hdrs}" "${mall_grpc_srcs}" "${mall_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_SOURCE_DIR}/protos"
        --cpp_out "${CMAKE_CURRENT_SOURCE_DIR}/protos"
        -I "${mall_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${mall_proto}"
      DEPENDS "${mall_proto}")

# grpc_proto
add_library(mall_grpc_proto
  ${mall_grpc_srcs}
  ${mall_grpc_hdrs}
  ${mall_proto_srcs}
  ${mall_proto_hdrs})
target_link_libraries(mall_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})




  add_executable(client "clientDemo.cc")
  target_link_libraries(client
  basic_grpc_proto
  Mylib
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})