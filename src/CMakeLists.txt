cmake_minimum_required(VERSION 3.5)

project(synchronized_thread LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(synchronized_thread
    main.cpp
    thread.h
    semaphore.h
    semaphore.cpp
    synchronized_thread.h
    synchronized_thread.cpp
    synchronized_future.h
    synchronized_future.cpp
    synchronized_task.h
)

if(UNIX AND NOT APPLE)
    target_link_libraries(synchronized_thread pthread) 
endif()
