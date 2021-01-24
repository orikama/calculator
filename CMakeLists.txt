cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(calculator CXX)


# if using conan
if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conaninfo.txt)
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
endif()


find_package(Boost REQUIRED)


set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")


# --------------- libcalc ---------------
set(libcalc_HEADERS_DIR "${INCLUDE_DIR}/libcalc")
set(libcalc_HEADERS
    ${libcalc_HEADERS_DIR}/calc.hpp
)

set(libcalc_SRC_DIR "${SRC_DIR}/libcalc")
set(libcalc_SRC
    ${libcalc_SRC_DIR}/calc.cpp
)

add_library(libcalc STATIC ${libcalc_SRC} ${libcalc_HEADERS})
target_include_directories(libcalc
    PUBLIC ${INCLUDE_DIR}
    PRIVATE ${Boost_INCLUDE_DIR}
)
target_compile_features(libcalc PUBLIC cxx_std_17)


# --------------- calculator ---------------
set(calculator_SRC_DIR "${SRC_DIR}/calculator")
set(calculator_SRC
    ${calculator_SRC_DIR}/main.cpp
)

add_executable(calculator ${calculator_SRC})
target_link_libraries(calculator PRIVATE libcalc)
