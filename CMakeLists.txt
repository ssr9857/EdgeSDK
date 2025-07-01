# cmake的最小版本
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(EdgeSDK)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall -fPIC") 

# 设置头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/
        ${PROJECT_SOURCE_DIR}/include/
        ${PROJECT_SOURCE_DIR}/3rd/jsoncpp/include/
        ${PROJECT_SOURCE_DIR}/3rd/mqtt/include/
        ${PROJECT_SOURCE_DIR}/3rd/rdkafka/include/)
# 设置生成SDK所需源文件位置
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_FILES)
# 设置生成的文件类型
add_library(edge_sdk SHARED ${SRC_FILES})

# 设置生成的库目标输出位置
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib) 
# 链接SDK需要的库
target_link_libraries(edge_sdk
                        ${PROJECT_SOURCE_DIR}/3rd/jsoncpp/lib/libjsoncpp.so
                        ${PROJECT_SOURCE_DIR}/3rd/mqtt/lib/libmosquitto.so
                        ${PROJECT_SOURCE_DIR}/3rd/rdkafka/lib/librdkafka.so.1
                        ${PROJECT_SOURCE_DIR}/3rd/rdkafka/lib/librdkafka++.so.1)

install(FILES ${PROJECT_SOURCE_DIR}/edge_interface.h DESTINATION ${PROJECT_SOURCE_DIR}/build/release/include/)
install(FILES ${LIBRARY_OUTPUT_PATH}/libedge_sdk.so DESTINATION ${PROJECT_SOURCE_DIR}/build/release/lib/) 


# 编译demo
add_executable(demo demo.cpp)
target_link_libraries(demo 
                        ${PROJECT_SOURCE_DIR}/3rd/jsoncpp/lib/libjsoncpp.so
                        ${PROJECT_SOURCE_DIR}/3rd/mqtt/lib/libmosquitto.so
                        ${PROJECT_SOURCE_DIR}/3rd/rdkafka/lib/librdkafka.so.1
                        ${PROJECT_SOURCE_DIR}/3rd/rdkafka/lib/librdkafka++.so.1
                        edge_sdk)
#生成可执行文件demo，demo.cpp已经编写好了，这个时候只需要链接到edge_sdk即可进行编译

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/build/demo DESTINATION ${PROJECT_SOURCE_DIR}/ PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

