# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project("scene")

set(jnilibs "${CMAKE_SOURCE_DIR}/../jniLibs")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -fexceptions -frtti")


include_directories(
        include
        include/assimp
        include/glm
        include/opencv2
        helper
        shader
        camera
        model
)


file(GLOB src-files
        helper/*.cpp
        helper/FileHelper.cpp
        helper/JNIHelper.cpp
        shader/Shader.cpp
        camera/GLCamera.cpp
        model/AssimpLoader.cpp
        model/AssimpModel.cpp
        SceneRender.cpp)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ${src-files})

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

set(ATLAS_ENGINE_SYSTEM_LIBS android EGL GLESv2 GLESv3 m)


add_library(assimp SHARED IMPORTED)
set_target_properties(assimp PROPERTIES IMPORTED_LOCATION ${jnilibs}/${ANDROID_ABI}/libassimp.so)

add_library(opencv4 SHARED IMPORTED)
set_target_properties(opencv4 PROPERTIES IMPORTED_LOCATION ${jnilibs}/${ANDROID_ABI}/libopencv_java4.so)

set(third-party-libs
        assimp
        opencv4)

target_link_libraries( # Specifies the target library.
                       native-lib
                       ${third-party-libs}
                       ${ATLAS_ENGINE_SYSTEM_LIBS}
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )