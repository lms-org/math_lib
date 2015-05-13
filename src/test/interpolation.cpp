#include "gtest/gtest.h"
#include "lms/math/interpolation.h"

TEST(Interpolation, linearInt) {
    using lms::math::linearInterpolation;

    bool result;
    int y;

    result = linearInterpolation<int>(10, 10, 100, 20, 55, y);
    EXPECT_TRUE(result);
    EXPECT_EQ(15, y);

    result = linearInterpolation<int>(10, 10, 10, 100, 10, y);
    EXPECT_FALSE(result) << "returned " << y;
}
