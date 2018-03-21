cmake_minimum_required(VERSION 3.2)

project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set (HW ./hw03)
set (TESTS_SOURCES
        ${HW}/tests/test_ip_filter.cpp)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(hw03_ip_filter ${HW}/ip_filter.cpp)

add_library(ip_filter_li ${HW}/ip_filter_li.cpp)

set (TEST test_ip_filter)
add_executable (${TEST} ${TESTS_SOURCES})

set_target_properties(hw03_ip_filter PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )

set_target_properties(${TEST} PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
       )

target_link_libraries(hw03_ip_filter ip_filter_li)

target_link_libraries(${TEST} ip_filter_li ${Boost_LIBRARIES})

install(TARGETS hw03_ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT saleksvik@gmail.com)

include (CPack)

enable_testing()

add_test(test_reversed_sort ${TEST})
