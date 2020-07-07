# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.8)


set(HEADER_FILE "build_number.h")
set(CACHE_FILE "BuildNumberCache.txt")

#Reading data from file + incrementation
IF(EXISTS ${CACHE_FILE})
    file(READ ${CACHE_FILE} BUILD_NUMBER)
    math(EXPR BUILD_NUMBER "${BUILD_NUMBER}+1")
ELSE()
    set(BUILD_NUMBER "1")
ENDIF()


#Update the cache
file(WRITE ${CACHE_FILE} "${BUILD_NUMBER}")

#Create the header
file(WRITE ${HEADER_FILE} "#ifndef BUILD_NUMBER_H\n#define BUILD_NUMBER_H\n\n#define BUILD_NUMBER ${BUILD_NUMBER}\n\n#endif")

project (ip_filter VERSION 0.0.${BUILD_NUMBER})

#SET(GTEST_ROOT ${PROJECT_SOURCE_DIR}/gtest)
SET(BUILD_SHARED_LIBS ON)




set(SOURCES
    main.cpp
    #lib.cpp
)
ADD_LIBRARY(Libs STATIC
    lib.cpp
)
add_executable(ip_filter ${SOURCES})

#find_package(GTest REQUIRED)
add_subdirectory("gtest" ${CMAKE_BINARY_DIR}/gtest)
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(test_version test_version.cpp)
target_link_libraries(test_version gtest gtest_main)
add_test(test_version test_version)



include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(ip_filter Libs)
target_link_libraries(test_version libs)

# Create a sources variable with a link to all cpp files to compile

configure_file(version.h.in version.h)

include(GoogleTest)


target_link_libraries(ip_filter
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                    )

target_include_directories(ip_filter
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)



# use particular C++ 14 standart
set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_version test_version)