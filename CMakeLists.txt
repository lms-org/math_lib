cmake_minimum_required(VERSION 2.8.12)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set ( SOURCES
    "src/stub.cpp"
    "src/curve.cpp"
    "src/math.cpp"
)

set (HEADERS
    "include/lms/math/interpolation.h"
    "include/lms/math/lookup_table.h"
    "include/lms/math/vertex.h"
    "include/lms/math/polyline.h"
    "include/lms/math/curve.h"
    "include/lms/math/math.h"
    "include/lms/math/convert.h"
    "include/lms/math/mathEigen.h"
)

set (TESTS
    "src/test/lookup_table.cpp"
    "src/test/interpolation.cpp"
    "src/test/convert.cpp"
    "src/test/vertex.cpp"
)

#set compiler flags
if((${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang") OR (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU"))
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wreturn-type -Wpedantic ")
endif()

#todo if
add_definitions(-DUSE_CEREAL)

include_directories("include")

add_library(lms_math SHARED ${SOURCES} ${HEADERS})
target_link_libraries(lms_math PRIVATE ${CONAN_LIBS})

message("Compile math_lib testing executable")
add_executable(math_lib_test ${TESTS})
target_link_libraries(math_lib_test PRIVATE lms_math ${CONAN_LIBS})
add_test(MathLib math_lib_test)


message("ADDED MATH_LIB")
