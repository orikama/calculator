cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(calculator CXX)


# if using conan
if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conaninfo.txt)
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
endif()


find_package(Boost REQUIRED)


set(calculator_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(calculator_SRC
    ${calculator_SRC_DIR}/main.cpp
)

add_executable(calculator ${calculator_SRC})
target_include_directories(calculator PRIVATE ${Boost_INCLUDE_DIR})
target_compile_features(calculator PRIVATE cxx_std_17)
