find_package(Protobuf REQUIRED)

set(RES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/message)
set(MESSAGE_SRC "")
file(MAKE_DIRECTORY ${RES_DIR})

set(MSG_PROTOS
    ${CMAKE_CURRENT_SOURCE_DIR}/cpu_load.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/cpu_softirq.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/cpu_stat.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/mem_info.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/net_info.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/service.proto
)

foreach(msg ${MSG_PROTOS})
        get_filename_component(FIL_WE ${msg} NAME_WE)

        list(APPEND MESSAGE_SRC "${RES_DIR}/${FIL_WE}.pb.cc")

        add_custom_command(
          OUTPUT "${RES_DIR}/${FIL_WE}.pb.cc"
                 "${RES_DIR}/${FIL_WE}.pb.h"
          COMMAND  ${PROTOBUF_PROTOC_EXECUTABLE}
          ARGS --cpp_out ${RES_DIR}
            -I ${CMAKE_CURRENT_SOURCE_DIR}
            ${msg}
          DEPENDS ${msg}
          COMMENT "Running C++ protocol buffer compiler on ${msg}"
          VERBATIM 
        )
endforeach()

add_library(message SHARED ${MESSAGE_SRC}) 
target_include_directories(message PUBLIC ${RES_DIR})  
target_link_libraries(message PRIVATE ${Protobuf_LIBRARIES}) 