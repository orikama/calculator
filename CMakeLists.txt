cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(calculator CXX)


# if using conan
if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conaninfo.txt)
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
endif()


find_package(Boost REQUIRED)


set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")


# --------------- libcalc ---------------
set(libcalc_HEADERS_DIR "${INCLUDE_DIR}/libcalc")
set(libcalc_HEADERS
    ${libcalc_HEADERS_DIR}/calc.hpp
    ${libcalc_HEADERS_DIR}/detail/ast.hpp
    ${libcalc_HEADERS_DIR}/detail/evaluator.hpp
    ${libcalc_HEADERS_DIR}/detail/grammar.hpp
)

set(libcalc_SRC_DIR "${SRC_DIR}/libcalc")
set(libcalc_SRC
    ${libcalc_SRC_DIR}/calc.cpp
    ${libcalc_SRC_DIR}/detail/evaluator.cpp
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


# --------------- libcalc TESTS ---------------
if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    include(CTest)

    #if(${BUILD_TESTING})
        #add_subdirectory(tests)
    set(libcalc_tests_SRC
        ${TESTS_DIR}/main.cpp
        ${TESTS_DIR}/test_libcalc_task.cpp
    )
    
    add_executable(libcalc_tests ${libcalc_tests_SRC})
    target_link_libraries(libcalc_tests
        PRIVATE libcalc
                Boost::unit_test_framework
    )
    
    add_test(
        NAME libcalc_tests
        COMMAND $<TARGET_FILE:libcalc_tests>
    )
    #endif()
endif()
