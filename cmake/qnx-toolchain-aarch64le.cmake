# 用于 ‌指定目标操作系统的名称‌，直接影响 CMake 的构建规则和编译策略
set(CMAKE_SYSTEM_NAME QNX)
# 用于 ‌标识目标处理器的架构类型‌，直接影响编译器的指令集优化和二进制兼容性
set(CMAKE_SYSTEM_PROCESSOR aarch64le)


# 在交叉编译环境下查找可执行程序（find_program）时搜索范围‌ 的变量，直接影响依赖程序的定位优先级和路径策略
if (NOT DEFINED CMAKE_FIND_ROOT_PATH_MODE_PROGRAM)
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
endif()
# 控制 find_library 对库文件的搜索范围
if (NOT DEFINED CMAKE_FIND_ROOT_PATH_MODE_LIBRARY)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
endif()
# 控制 find_package 对软件包的搜索逻辑
if (NOT DEFINED CMAKE_FIND_ROOT_PATH_MODE_PACKAGE)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
endif()
# 控制 find_path 对头文件的搜索范围
if (NOT DEFINED CMAKE_FIND_ROOT_PATH_MODE_INCLUDE)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
endif()


#QNX_HOST=/home/dve/work/code/360/qnx-sdk_local8155/qnx/qnx-sdp/host/linux/x86_64
#QNX_TARGET=/home/dve/work/code/360/qnx-sdk_local8155/qnx/qnx-sdp/target/qnx7
#MAKEFLAGS=-I/home/dve/work/code/360/qnx-sdk_local8155/qnx/qnx-sdp/target/qnx7/usr/include
# 指定交叉编译环境下目标系统的根路径‌ 的关键变量，直接影响 find_* 系列命令（如 find_path、find_library）的搜索优先级和路径范围
set(CMAKE_FIND_ROOT_PATH $ENV{QNX_TARGET};$ENV{QNX_TARGET}/${CMAKE_SYSTEM_PROCESSOR};${QNX_HOST})


set(_qnx_toolchain_arch gcc_ntoaarch64le)

set(CMAKE_C_COMPILER qcc)
#指定 C 编译器生成代码的目标架构或平台‌ 的变量，主要应用于跨平台编译场景中
set(CMAKE_C_COMPILER_TARGET ${_qnx_toolchain_arch})
set(CMAKE_CXX_COMPILER q++)
set(CMAKE_CXX_COMPILER_TARGET ${_qnx_toolchain_arch})

#该工具可移除可执行文件及动态库中的符号表和调试信息，从而减小文件体积，提升发布版本性能
set(CMAKE_STRIP $ENV{QNX_HOST}/usr/bin/ntoaarch64-strip)
#静态库归档工具路径‌（如 GNU ar），用于生成静态库文件（.a 或 .lib）和管理目标文件合并
set(CMAKE_AR $ENV{QNX_HOST}/usr/bin/ntoaarch64-ar)

#指定交叉编译时目标系统的根目录路径‌ 
set(CMAKE_SYSROOT $ENV{QNX_TARGET})