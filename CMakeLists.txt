cmake_minimum_required(VERSION 3.10)

project(RayTracer)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DOUTPUT_DIR="${PROJECT_SOURCE_DIR}/picture/")

find_package(directxmath CONFIG REQUIRED)
find_package(OpenCV REQUIRED)
find_package(OpenMP REQUIRED)
aux_source_directory(src DIR_SRC)

add_executable(${PROJECT_NAME} ${DIR_SRC})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/src/pch.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${DirectXMath_LIBS}
    ${OpenMP_LIBS}
    ${OpenCV_LIBS}
)
