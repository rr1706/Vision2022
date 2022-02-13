file(GLOB msgs ${CMAKE_CURRENT_SOURCE_DIR}/*.proto)
set(messages_INCLUDES ${CMAKE_CURRENT_BINARY_DIR})

get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)

add_library(messages ${msgs})
target_include_directories(messages PUBLIC ${messages_INCLUDES})
target_link_libraries(messages protobuf::protobuf gRPC::gRPC)

# compile the message types
protobuf_generate(TARGET messages LANGUAGE cpp)

# compile the GRPC services
protobuf_generate(
    TARGET messages
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}"
) 
