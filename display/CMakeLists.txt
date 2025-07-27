set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt6 REQUIRED COMPONENTS Core Widgets)


add_executable(display ${CMAKE_CURRENT_SOURCE_DIR}/src/display.cc)
target_include_directories(display PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(display PRIVATE
    Qt6::Core
    Qt6::Widgets
    client
)

