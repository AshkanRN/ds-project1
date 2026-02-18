cmake_minimum_required(VERSION 3.20)
project(HospitalSystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(HospitalSystem
        main.cpp
        src/medicine.cpp
        src/queue.cpp
        src/user.cpp
        src/clinic.cpp
        src/doctor.cpp
        src/emergency.cpp
)

target_include_directories(HospitalSystem PRIVATE include/)