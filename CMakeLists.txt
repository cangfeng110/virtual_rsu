cmake_minimum_required(VERSION 3.1)

project(virtual_light)

add_compile_options(-std=c++11)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/thirdparty
    ${CMAKE_CURRENT_SOURCE_DIR}/src/thirdparty/mqtt
    ${CMAKE_CURRENT_SOURCE_DIR}/src/thirdparty/mqttc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/thirdparty/nlohmann
)

add_definitions("-Wall -g")

aux_source_directory(src/ SRC)

add_executable(virtual_light ${SRC})

add_executable(async_subscribe async_subscribe.cpp src/light_message.cpp src/callback.cpp)

target_link_libraries(virtual_light  paho-mqtt3as paho-mqttpp3 pthread)

target_link_libraries(async_subscribe  paho-mqtt3as paho-mqttpp3 pthread)