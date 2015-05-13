set ( SOURCES
    "src/lookup_table_test.cpp"
)

set (HEADERS
	"include/lms/math/interpolation.h"
	"include/lms/math/lookup_table.h"
	"include/lms/math/vertex.h"
	"include/lms/math/polyline.h"
	"include/lms/math/curve.h"
	"include/lms/math/math.h"
)

include_directories("include")

add_library(math_lib SHARED ${SOURCES} ${HEADERS})

add_executable(lookup_table_test "src/lookup_table_test.cpp")
target_link_libraries(lookup_table_test PRIVATE math_lib)
