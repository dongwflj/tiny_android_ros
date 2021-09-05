cmake_minimum_required(VERSION 3.4.1)

add_library(
             TomatoNN
             SHARED
             src/main/cpp/NnWrapper.cpp
             )
find_library(
          android-lib
          android
          )

include(AndroidNdkModules)
android_ndk_import_module_cpufeatures()

add_library(
    caffe2
    STATIC
    IMPORTED
    )
set_target_properties(
    caffe2
    PROPERTIES IMPORTED_LOCATION
    #${CMAKE_CURRENT_LIST_DIR}/src/main/jniLibs/${ANDROID_ABI}/libCaffe2_CPU.a
    ${CMAKE_CURRENT_LIST_DIR}/src/main/jniLibs/${ANDROID_ABI}/libCaffe2.a
    )

add_library(
    caffe2_protos
    STATIC
    IMPORTED
    )
set_target_properties(
    caffe2_protos
    PROPERTIES IMPORTED_LOCATION
    ${CMAKE_CURRENT_LIST_DIR}/src/main/jniLibs/${ANDROID_ABI}/libCaffe2_protos.a
    )

add_library(
    thread_pool
    STATIC
    IMPORTED
    )
set_target_properties(
    thread_pool
    PROPERTIES IMPORTED_LOCATION
    #${CMAKE_CURRENT_LIST_DIR}/src/main/jniLibs/${ANDROID_ABI}/libCAFFE2_PTHREADPOOL.a
    ${CMAKE_CURRENT_LIST_DIR}/src/main/jniLibs/${ANDROID_ABI}/libpthreadpool.a
    )
add_library(
    glog
    SHARED
    IMPORTED
    )
set_target_properties(
    glog
    PROPERTIES IMPORTED_LOCATION
    ${CMAKE_CURRENT_LIST_DIR}/src/main/jniLibs/${ANDROID_ABI}/libglog.so
    )

add_library(
    protobuf
    SHARED
    IMPORTED
    )
set_target_properties(
    protobuf
    PROPERTIES IMPORTED_LOCATION
    ${CMAKE_CURRENT_LIST_DIR}/src/main/jniLibs/${ANDROID_ABI}/libprotobuf.a
    )

add_library(
    NNPACK
    STATIC
    IMPORTED
    )
set_target_properties(
    NNPACK
    PROPERTIES IMPORTED_LOCATION
    #${CMAKE_CURRENT_LIST_DIR}/src/main/jniLibs/${ANDROID_ABI}/libCAFFE2_NNPACK.a
    ${CMAKE_CURRENT_LIST_DIR}/src/main/jniLibs/${ANDROID_ABI}/libnnpack.a
    )

add_library(
    onnx
    STATIC
    IMPORTED
    )
set_target_properties(
    onnx
    PROPERTIES IMPORTED_LOCATION
    ${CMAKE_CURRENT_LIST_DIR}/src/main/jniLibs/${ANDROID_ABI}/libonnx.a
    )

add_library(
    onnx_proto
    STATIC
    IMPORTED
    )
set_target_properties(
    onnx_proto
    PROPERTIES IMPORTED_LOCATION
    ${CMAKE_CURRENT_LIST_DIR}/src/main/jniLibs/${ANDROID_ABI}/libonnx_proto.a
    )

add_library(
    nomnigraph
    STATIC
    IMPORTED
    )
set_target_properties(
    nomnigraph
    PROPERTIES IMPORTED_LOCATION
    ${CMAKE_CURRENT_LIST_DIR}/src/main/jniLibs/${ANDROID_ABI}/libnomnigraph.a
    )

add_library(
    nnpack_refer
    STATIC
    IMPORTED
    )
set_target_properties(
    nnpack_refer
    PROPERTIES IMPORTED_LOCATION
    ${CMAKE_CURRENT_LIST_DIR}/src/main/jniLibs/${ANDROID_ABI}/libnnpack_reference_layers.a
    )
add_library(
    protobuf_lite
    SHARED
    IMPORTED
    )
set_target_properties(
    protobuf_lite
    PROPERTIES IMPORTED_LOCATION
    ${CMAKE_CURRENT_LIST_DIR}/src/main/jniLibs/${ANDROID_ABI}/libprotobuf-lite.a
    )

add_library(
    cpuinfo
    SHARED
    IMPORTED
    )
set_target_properties(
    cpuinfo
    PROPERTIES IMPORTED_LOCATION
    ${CMAKE_CURRENT_LIST_DIR}/src/main/jniLibs/${ANDROID_ABI}/libcpuinfo.a
    )

include_directories( src/main/cpp
                     /Users/ewen/01_work/github/OpenCV-2.4.9-android-sdk/sdk/native/jni/include
                     )

find_library(
     log-lib
     log
     )

target_link_libraries(
                       TomatoNN
                       -Wl,--whole-archive
                       caffe2
                       caffe2_protos
                       -Wl,--no-whole-archive
                       NNPACK
                       thread_pool
                       glog
                       protobuf
                       cpufeatures
                       onnx
                       onnx_proto
                       nomnigraph
                       nnpack_refer
                       protobuf_lite
                       cpuinfo
                       ${log-lib}
                       ${android-lib})