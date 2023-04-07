cmake_minimum_required(VERSION 3.25)
project(testlibpd)

set(CMAKE_CXX_STANDARD 17)

# pthreads-win32
set(PTHREADS_INCLUDE_DIR 3rd_party/pthread-win32)
set(CMAKE_THREAD_LIBS_INIT ${CMAKE_BINARY_DIR}/pthreadVC3.lib)
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
