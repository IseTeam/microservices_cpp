cmake_minimum_required(VERSION 3.0.0)
project("Microservices-cpp" VERSION 1.0.0 LANGUAGES CXX)

#
# 编译选项
#

option(BUILD_TESTS "Build unit tests." ON)

#
# 配置
#

set(CMAKE_CXX_STANDARD 11)
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_DIR  "${PROJECT_SOURCE_DIR}/src")
set(SOURCE_MODEL_DIR "${PROJECT_SOURCE_DIR}/src/model")
set(SOURCE_DISCOVERY_DIR "${PROJECT_SOURCE_DIR}/src/discovery")

# Windows MSVC 编译器
if(CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_WIN32_WINNT=0x0601 /W4 /wd4068 /wd4702 /wd4996 /wd4265" )
endif()

# 除了windows的平台
if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -pedantic -Wno-unknown-pragmas -Wno-deprecated-declarations -Wno-non-virtual-dtor")
endif()

# 设置CMake Module的查找路径
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake" )

# 寻找日志库的外部依赖
find_package(spdlog REQUIRED)

include_directories(${INCLUDE_DIR} SYSTEM ${spdlog_INCLUDE})

if(BUILD_TESTS)
  enable_testing()
endif()

aux_source_directory(${SOURCE_DIR} ALL_SRC)
aux_source_directory(${SOURCE_MODEL_DIR} MODEL_SRC)
aux_source_directory(${SOURCE_DISCOVERY_DIR} DISCOVERY_SRC)
add_executable(main ${ALL_SRC} ${MODEL_SRC} ${DISCOVERY_SRC})

target_link_libraries(main mysqlclient)