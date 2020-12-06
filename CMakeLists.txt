cmake_minimum_required(VERSION 3.10)

# set the project name
project(final)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# add_definitions(-std=c++11 -O3 -pthread )
# add the executable
add_executable(final multithreads/9.1/main.cpp)

target_link_libraries(final ${CMAKE_THREAD_LIBS_INIT} )
