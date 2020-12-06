cmake_minimum_required(VERSION 2.8)

# set the project name
project(final)
add_definitions("-std=c++11")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# add the executable
add_executable(final multithreads/9.1/main.cpp)

target_link_libraries(final ${CMAKE_THREAD_LIBS_INIT} )
