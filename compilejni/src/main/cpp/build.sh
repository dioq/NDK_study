#!/bin/sh
ANDROID_NDK=~/Library/Android/Sdk/ndk/25.2.9519653
build_file=build

rm -rf ${build_file}


# 工具链文件支持
cmake \
    -DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK}/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a \
    -DANDROID_PLATFORM=android-29 \
	-B ${build_file}

cmake --build ${build_file}
