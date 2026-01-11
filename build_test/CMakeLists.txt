cmake_minimum_required(VERSION 3.16)
project(test_wifi_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

add_executable(test_wifi
    ../test_wifi.cpp
    ../src/ssl_client.cpp
)

target_link_libraries(test_wifi PRIVATE Qt6::Core Qt6::Network)
target_include_directories(test_wifi PRIVATE ${CMAKE_SOURCE_DIR}/..)
