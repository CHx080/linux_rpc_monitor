set(ALL_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cpu_load.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cpu_softirq.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cpu_stat.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mem_info.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/net_info.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/util.cc
)
add_library(monitor SHARED ${ALL_SRC})
target_include_directories(monitor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(monitor PRIVATE info)
