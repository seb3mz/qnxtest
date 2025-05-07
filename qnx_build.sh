source /home/dve/work/code/360/qnx-sdk_local8155/qnx/qnx-sdp/qnxsdp-env.sh

cmake \
-DCMAKE_TOOLCHAIN_FILE=./cmake/qnx-toolchain-aarch64le.cmake \
-G 'Unix Makefiles' \
-B ./build \
-S .                  

#-DCMAKE_BUILD_TYPE=Debug \
# -G 指定 ‌构建系统生成器‌，决定 CMake 生成的项目文件类型
# -B 指定构建目录
# -S 指定包含 CMakeLists.txt源代码目录 