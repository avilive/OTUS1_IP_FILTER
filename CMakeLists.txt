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

SET(BUILD_SHARED_LIBS ON)

#------------------------------------------
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
find_package(Threads REQUIRED)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
ExternalProject_Add(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  UPDATE_COMMAND ""
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON)

ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIRS ${source_dir}/googletest/include)
set(GMOCK_INCLUDE_DIRS ${source_dir}/googlemock/include)

ExternalProject_Get_Property(googletest binary_dir)
##set(GTEST_LIBRARY_PATH ${binary_dir}/googlemock/gtest/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a)
set(GTEST_LIBRARY_PATH ${binary_dir}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}gtestd.lib)
set(GTEST_LIBRARY gtest)
add_library(${GTEST_LIBRARY} UNKNOWN IMPORTED)

set_target_properties(${GTEST_LIBRARY} PROPERTIES
  IMPORTED_LOCATION ${GTEST_LIBRARY_PATH})

set_target_properties(${GTEST_LIBRARY} PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")

add_dependencies(${GTEST_LIBRARY} googletest)

##set(GTEST_MAIN_LIBRARY_PATH ${binary_dir}/googlemock/gtest/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main.a)
set(GTEST_MAIN_LIBRARY_PATH ${binary_dir}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_maind.lib)
set(GTEST_MAIN_LIBRARY gtest_main)
add_library(${GTEST_MAIN_LIBRARY} UNKNOWN IMPORTED)
set_target_properties(${GTEST_MAIN_LIBRARY} PROPERTIES
  IMPORTED_LOCATION ${GTEST_MAIN_LIBRARY_PATH}
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")
add_dependencies(${GTEST_MAIN_LIBRARY} googletest)



#------------------------------------------


set(SOURCES
    main.cpp

)
ADD_LIBRARY(Libs STATIC
    lib.cpp
)
include(GoogleTest)

add_executable(ip_filter ${SOURCES})

add_executable(test_version test_version.cpp)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(ip_filter Libs)

target_link_libraries(test_version libs gtest gtest_main )
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
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

#if (MSVC)
 #   target_compile_options(${SOURCES} PRIVATE
 #       /W4
#    )
#    target_compile_options(Libs PRIVATE
#        /W4
#    )
 #   target_compile_options(test_version PRIVATE
 #       /W4
 #   )
#else ()
#if(NOT MSVC)
#    target_compile_options(${SOURCES} PRIVATE
 #       -Wall -Wextra -pedantic -Werror
#    )
 #   target_compile_options(Libs PRIVATE
 #       -Wall -Wextra -pedantic -Werror
 #   )
 #   target_compile_options(test_version PRIVATE
 #       -Wall -Wextra -pedantic -Werror
 #   )
#endif()



install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_version test_version)
