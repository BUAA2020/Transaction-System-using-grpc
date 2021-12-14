# Proto file
get_filename_component(seckill_proto "${CMAKE_CURRENT_SOURCE_DIR}/protos/SecKillService.proto" ABSOLUTE)
get_filename_component(seckill_proto_path "${seckill_proto}" PATH)

# Generated sources
set(seckill_proto_srcs "${CMAKE_CURRENT_SOURCE_DIR}/protos/SecKillService.pb.cc")
set(seckill_proto_hdrs "${CMAKE_CURRENT_SOURCE_DIR}/protos/SecKillService.pb.h")
set(seckill_grpc_srcs "${CMAKE_CURRENT_SOURCE_DIR}/protos/SecKillService.grpc.pb.cc")
set(seckill_grpc_hdrs "${CMAKE_CURRENT_SOURCE_DIR}/protos/SecKillService.grpc.pb.h")
add_custom_command(
      OUTPUT "${seckill_proto_srcs}" "${seckill_proto_hdrs}" "${seckill_grpc_srcs}" "${seckill_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_SOURCE_DIR}/protos"
        --cpp_out "${CMAKE_CURRENT_SOURCE_DIR}/protos"
        -I "${seckill_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${seckill_proto}"
      DEPENDS "${seckill_proto}")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/protos")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/")

# grpc_proto
add_library(seckill_grpc_proto
  ${seckill_grpc_srcs}
  ${seckill_grpc_hdrs}
  ${seckill_proto_srcs}
  ${seckill_proto_hdrs})
target_link_libraries(seckill_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})


