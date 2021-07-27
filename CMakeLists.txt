cmake_minimum_required(VERSION 3.14)

project(tcp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(Qt5Svg)
find_package(Qt5Network)

add_executable(${PROJECT_NAME} main.cpp tcp_client.cpp tcp_server.cpp)

target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${Qt5Svg_LIBRARIES}
    ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Network_LIBRARIES})
