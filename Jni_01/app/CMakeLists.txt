# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
#设置最小的cmake编译版本
cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#设置动态库输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/main/jniLibso/${ANDROID_ABI})
add_library( # Sets the name of the library.
        #设置库名称
        native_lib
        #设置库的输出方式（动态/静态）
        # Sets the library as a shared library.
        SHARED
        #设置库所包含的源码
        # Provides a relative path to your source file(s).
        src/main/cpp/native-lib.cpp
        src/main/cpp/JniTest.h
        src/main/cpp/JniTest.c)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.
#查找库
find_library(
        #依赖库的别名
        # Sets the name of the path variable.
        log-lib
        #NDK依赖库的名称
        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
#动态库所需链接的依赖库
target_link_libraries( # Specifies the target library.
        native_lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})