cmake_minimum_required(VERSION 3.2)

project(helloworld VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set (TESTS_SOURCES
        ./tests/test_main.cpp)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

add_executable(hw01_helloworld main.cpp)

add_library(lib_helloworld lib_helloworld.cpp)

set (TEST test_helloworld)
add_executable (${TEST} ${TESTS_SOURCES})

set_target_properties(hw01_helloworld ${TEST} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )

set_target_properties(${TEST} PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
        )

target_link_libraries(${TEST}
        ${Boost_LIBRARIES}
        lib_helloworld
        )

target_link_libraries(hw01_helloworld lib_helloworld)

install(TARGETS hw01_helloworld RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT saleksvik@gmail.com)

include (CPack)

enable_testing()

add_test(test_version_valid test_main)
