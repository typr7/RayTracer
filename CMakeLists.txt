cmake_minimum_required(VERSION 3.10)

project(RayTracer)

set(CMAKE_CXX_STANDARD 20)

find_package(directxmath CONFIG REQUIRED)

aux_source_directory(src DIR_SRC)

add_executable(${PROJECT_NAME} ${DIR_SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Microsoft::DirectXMath
)