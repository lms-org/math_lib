#include <cmath>

#include "gtest/gtest.h"
#include "lms/math/polyline.h"

namespace lms {
namespace math {

TEST(Polyline2f,firstOrthogonalDistance){
    lms::math::polyLine2f l;
    l.points().push_back(lms::math::vertex2f(0,0));
    l.points().push_back(lms::math::vertex2f(1,0));
    EXPECT_EQ(2,l.points().size());
    float t,o;
    l.firstOrthogonalDistance(lms::math::vertex2f(0.5,0),o,t);
    EXPECT_FLOAT_EQ(0,o);
    EXPECT_FLOAT_EQ(0.5,t);
    l.firstOrthogonalDistance(lms::math::vertex2f(0.5,0.5),o,t);
    EXPECT_FLOAT_EQ(0.5,o);
    EXPECT_FLOAT_EQ(0.5,t);
    l.firstOrthogonalDistance(lms::math::vertex2f(0.5,-0.5),o,t);
    EXPECT_FLOAT_EQ(-0.5,o);
    EXPECT_FLOAT_EQ(0.5,t);
}

}
}
