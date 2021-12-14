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

