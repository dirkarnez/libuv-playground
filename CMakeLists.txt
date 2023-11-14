cmake_minimum_required(VERSION 3.18)

project("libuv-playground")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

find_package(libuv REQUIRED) # PATHS "P:\\Downloads\\cpp-libraries\\portaudio\\build\\cmake\\portaudio")

if(libuv_FOUND)
    message(STATUS "YES")
else()
    message(STATUS "NO")
endif()

add_executable(${PROJECT_NAME}
    "src/main.cpp"
)

target_link_libraries(${PROJECT_NAME} libuv::uv_a)
