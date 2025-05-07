# 设置 cmake 最低版本
cmake_minimum_required(VERSION 3.5)

# 设置项目名称
set(PROJ_NAME qnxtest)
project (${PROJ_NAME})

message("${PROJ_NAME} begin Make")
# 输出编译详细过程
set(CMAKE_VERBOSE_MAKEFILE ON)

# 设置顶层路径
set(PROJROOT ${CMAKE_SOURCE_DIR})

# 设置编译生成文件类型
#set(CMAKE_BUILD_TYPE Debug)
#静态库生成路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJROOT}/build/lib/Debug)   
# 动态库生成路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJROOT}/build/lib/Debug)
#可执行文件生成路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJROOT}/build/bin/Debug)   

# 设置源文件路径
set(SRC_LIST "./main.cpp")

# 设置编译选项
#-Wall：启用所有常见的编译警告
#-O2：启用较高水平的优化。其他优化级别有 -O0（无优化）、-O1、-O3 和 -Os（优化代码大小
#-std=gnu++11：指定使用 GNU 扩展的 C++11 标准，在 ISO C++11 标准基础上，‌启用 GNU 扩展语法‌
set(LOCAL_CXXFLAGS -O2 -Wall -std=gnu++11)

#是 Ceres Solver 库的编译宏，用于显式指定使用 ‌C++11 标准线程库‌（如 std::thread）实现多线程优化
add_definitions(-DCERES_USE_CXX11_THREADS)

# 设置编译器

# cmake 添加编译选项
add_compile_options(${LOCAL_CXXFLAGS})

# cmake 添加可执行文件
add_executable(${PROJ_NAME} ${SRC_LIST})
