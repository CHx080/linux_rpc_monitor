find_package(Protobuf REQUIRED)

set(PROTO_DFILE_DIR ${CMAKE_CURRENT_BINARY_DIR}/message) #protoc编译后的文件存放路径
set(PROTO_SFILE 
  ${CMAKE_CURRENT_SOURCE_DIR}/cpu_load.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/cpu_softirq.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/cpu_stat.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/mem_info.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/net_info.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/service.proto
) #proto文件路径

file(MAKE_DIRECTORY ${PROTO_DFILE_DIR})
set(PROTO_SRC_OBJECTS "")

foreach(item ${PROTO_SFILE})
  get_filename_component(item_name ${item} NAME_WE)
  add_custom_command(
    OUTPUT ${PROTO_DFILE_DIR}/${item_name}.pb.h ${PROTO_DFILE_DIR}/${item_name}.pb.cc
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS --cpp_out ${PROTO_DFILE_DIR} -I ${CMAKE_CURRENT_SOURCE_DIR} ${item}
    COMMENT "Running protoc to ${item}"
    VERBATIM 
  )  
  list(APPEND PROTO_SRC_OBJECTS ${PROTO_DFILE_DIR}/${item_name}.pb.cc)
endforeach()

add_custom_target(proto ALL DEPENDS ${PROTO_SRC_OBJECTS})
add_library(info SHARED ${PROTO_SRC_OBJECTS})
add_dependencies(info proto)
target_sources(info PRIVATE ${PROTO_CPP_SRC})
target_include_directories(info PUBLIC ${PROTO_DFILE_DIR})
target_link_libraries(info PUBLIC ${Protobuf_LIBRARIES})