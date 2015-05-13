#include "gtest/gtest.h"
#include "lms/math/interpolation.h"

TEST(Interpolation, linearInt) {
    using lms::math::linearInterpolation;

    bool result;
    int y;

    // simple interpolation
    result = linearInterpolation<int>(10, 10, 100, 20, 55, y);
    EXPECT_TRUE(result);
    EXPECT_EQ(15, y);

    // dx == 0
    result = linearInterpolation<int>(10, 10, 10, 100, 10, y);
    EXPECT_FALSE(result) << "returned " << y;

    // extrapolation
    result = linearInterpolation<int>(10, 10, 20, 100, 0, y);
    EXPECT_TRUE(result);
    EXPECT_EQ(-80, y);
}

TEST(Interpolation, linearFloat) {
    using lms::math::linearInterpolation;

    bool result;
    float y;

    // simple interpolation
    result = linearInterpolation<float>(-10, 1, 10, 2, 0, y);
    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(1.5, y);

    // dx == 0
    result = linearInterpolation<float>(10, 10, 10, 100, 20, y);
    EXPECT_FALSE(result);

    // extrapolation
    result = linearInterpolation<float>(1, 0, 2, 0.5, 3, y);
    EXPECT_TRUE(y);
    EXPECT_FLOAT_EQ(1, y);
}
