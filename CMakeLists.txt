cmake_minimum_required(VERSION 3.12)
project(Monitor)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Release)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 添加子目录（必须在定义函数前调用）
add_subdirectory(protocol)
add_subdirectory(monitor)
add_subdirectory(rpc)
add_subdirectory(display)

# 设置安装前缀（默认 /usr/local）
set(CMAKE_INSTALL_PREFIX "/usr/local")
set(CMAKE_INSTALL_RPATH "$ORIGIN")  
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE) #动态库路径
# 递归获取所有目标的函数
function(get_all_targets_recursive out_var dir)
    get_property(subdirs DIRECTORY ${dir} PROPERTY SUBDIRECTORIES)
    foreach(subdir ${subdirs})
        get_all_targets_recursive(${out_var} ${subdir})
    endforeach()

    get_property(current_targets DIRECTORY ${dir} PROPERTY BUILDSYSTEM_TARGETS)
    list(APPEND ${out_var} ${current_targets})
    set(${out_var} ${${out_var}} PARENT_SCOPE)
endfunction()

function(auto_install_targets)
    set(all_targets)
    get_all_targets_recursive(all_targets ${CMAKE_SOURCE_DIR})
    
    foreach(target ${all_targets})
        get_target_property(target_type ${target} TYPE)
        if(target_type STREQUAL "EXECUTABLE")
            install(
                TARGETS ${target}
                RUNTIME DESTINATION bin  # 自动拼接 ${CMAKE_INSTALL_PREFIX}/bin
            )
        elseif(target_type STREQUAL "SHARED_LIBRARY")
            install(
                TARGETS ${target}
                LIBRARY DESTINATION lib  # 自动拼接 ${CMAKE_INSTALL_PREFIX}/lib
            )
        elseif(target_type STREQUAL "STATIC_LIBRARY")
            install(
                TARGETS ${target}
                ARCHIVE DESTINATION lib  # 自动拼接 ${CMAKE_INSTALL_PREFIX}/lib
            )
        endif()
    endforeach()
endfunction()

# 执行安装配置
auto_install_targets()