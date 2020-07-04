# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.8)


# Set the project name
if (DEFINED TRAVIS_BUILD_NUMBER)
    project (ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project (ip_filter VERSION 0.0.1)
endif()
enable_testing()


SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:\\Boost\\boost_1_65_1")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:\\Boost\\boost_1_65_1\\stage\\lib")
SET(BOOST_ROOT "C:\\Boost\\boost_1_65_1")


#find_package(Boost REQUIRED)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)


IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()


# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    main.cpp
    lib.cpp
    test_version.cpp
)

configure_file(version.h.in version.h)


# Add an executable with the above sources
add_executable(ip_filter ${SOURCES})
#add_library(ip_filter src/lib.cpp)
#add_executable(test_version src/test_version.cpp)
# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/


#target_link_libraries(ip_filter
  #                    ${Boost_FILESYSTEM_LIBRARY}
 #                     ${Boost_SYSTEM_LIBRARY}
 #                     ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
 #                     )

target_include_directories(ip_filter
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)



 #target_link_libraries(ip_filter_cli PRIVATE
 #   ip_filter
#)


# use particular C++ 14 standart
set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_version test_version)
