cmake_minimum_required(VERSION 4.3)

project(Project1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project1
        src/main.cpp
        src/Resource.cpp
        src/Reservation.cpp
        src/ReservationManager.cpp

        include/Resource.h
        include/Reservation.h
        include/ReservationManager.h
)

target_include_directories(Project1 PRIVATE include)