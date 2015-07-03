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
)

set (TESTS
    "src/test/lookup_table.cpp"
    "src/test/interpolation.cpp"
    "src/test/convert.cpp"
    "src/test/vertex.cpp"
)

include_directories("include")

add_library(math_lib SHARED ${SOURCES} ${HEADERS})

if(USE_GOOGLETEST)
    message("Compile math_lib testing executable")
    add_executable(math_lib_test ${TESTS})
    target_link_libraries(math_lib_test PRIVATE math_lib gtest gtest_main)
    add_test(MathLib math_lib_test)
endif()
