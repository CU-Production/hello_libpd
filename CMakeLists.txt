cmake_minimum_required(VERSION 3.25)
project(testlibpd)

set(CMAKE_CXX_STANDARD 17)

# pthreads-win32
include_directories(3rd_party/pthread-win32)
add_subdirectory(3rd_party/pthread-win32)

# libpd
add_subdirectory(3rd_party/libpd)

add_executable(testlibpd-capi capi.cpp)
target_link_libraries(testlibpd-capi PRIVATE libpd)
target_include_directories(testlibpd-capi
        PRIVATE 3rd_party/libpd/libpd_wrapper)

add_executable(testlibpd-cppapi cppapi.cpp)
target_link_libraries(testlibpd-cppapi PRIVATE libpd)
target_include_directories(testlibpd-cppapi
        PRIVATE 3rd_party/libpd/libpd_wrapper
        PRIVATE 3rd_party/libpd/cpp)

add_executable(libpd-miniaudio libpd-miniaudio.cpp)
target_link_libraries(libpd-miniaudio PRIVATE libpd)
target_include_directories(libpd-miniaudio
        PRIVATE 3rd_party/libpd/libpd_wrapper
        PRIVATE 3rd_party/libpd/cpp
        PRIVATE 3rd_party/miniaudio)
