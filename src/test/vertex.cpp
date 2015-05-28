#include <cmath>

#include "gtest/gtest.h"
#include "lms/math/vertex.h"

TEST(Vertex2, lengthSquared) {
    using lms::math::vertex2f;
    using lms::math::vertex2i;

    // vertex2f
    // simple case
    EXPECT_FLOAT_EQ(194, vertex2f(5, 13).lengthSquared());

    // zero vector
    EXPECT_FLOAT_EQ(0, vertex2f(0, 0).lengthSquared());

    // negative values
    EXPECT_FLOAT_EQ(229, vertex2f(-2, 15).lengthSquared());
    EXPECT_FLOAT_EQ(229, vertex2f(15, -2).lengthSquared());

    // vertex2i
    // simple case
    EXPECT_FLOAT_EQ(25, vertex2i(3, 4).lengthSquared());

    // zero vector
    EXPECT_FLOAT_EQ(0, vertex2i(0, 0).lengthSquared());

    // negative values
    EXPECT_FLOAT_EQ(169, vertex2i(-12, 5).lengthSquared());
    EXPECT_FLOAT_EQ(25, vertex2i(3, -4).lengthSquared());
}

TEST(Vertex2, angle) {
    using lms::math::vertex2f;

    // all four directions
    EXPECT_FLOAT_EQ(0, vertex2f(1, 0).angle());
    EXPECT_FLOAT_EQ(M_PI_2, vertex2f(0, 1).angle());
    EXPECT_FLOAT_EQ(M_PI, vertex2f(-1, 0).angle());
    EXPECT_FLOAT_EQ(- M_PI_2, vertex2f(0, -1).angle());

    EXPECT_FLOAT_EQ(M_PI_4, vertex2f(1, 1).angle());
}

TEST(Vertex2, add) {
    using lms::math::vertex2f;

    // operator +
    EXPECT_EQ(vertex2f(6, 8), vertex2f(-2, 4) + vertex2f(8, 4));

    // operator +=
    vertex2f a(8, 4);
    vertex2f b(-3, 15);
    EXPECT_EQ(vertex2f(5, 19), a += b);
    EXPECT_EQ(vertex2f(5, 19), a);
    EXPECT_EQ(vertex2f(-3, 15), b);
}

TEST(Vertex2, sub) {
    using lms::math::vertex2f;

    // operator -
    EXPECT_EQ(vertex2f(-10, 0), vertex2f(-2, 4) - vertex2f(8, 4));

    // operator -=
    vertex2f a(8, 4);
    vertex2f b(-3, 15);
    EXPECT_EQ(vertex2f(11, -11), a -= b);
    EXPECT_EQ(vertex2f(11, -11), a);
    EXPECT_EQ(vertex2f(-3, 15), b);
}

TEST(Vertex2, explicitConversion) {
    using lms::math::vertex2f;
    using lms::math::vertex2i;

    // from 2i to 2f
    EXPECT_EQ(vertex2f(2,3), vertex2f(vertex2i(2,3)));

    // from 2f to 2i
    EXPECT_EQ(vertex2i(2,3), vertex2i(vertex2f(2,3)));
    EXPECT_EQ(vertex2i(2,3), vertex2i(vertex2f(2.1,3.9)));
}

TEST(Vertex2, mul) {
    using lms::math::vertex2f;

    // operator *
    EXPECT_EQ(vertex2f(-6, 12), vertex2f(-2, 4) * 3);

    // operator *=
    vertex2f a(8, 1);
    EXPECT_EQ(vertex2f(24, 3), a *= 3);
    EXPECT_EQ(vertex2f(24, 3), a);
}

TEST(Vertex2, div) {
    using lms::math::vertex2f;

    // operator *
    EXPECT_EQ(vertex2f(-4, 1), vertex2f(-12, 3) / 3);

    // operator *=
    vertex2f a(24, -4);
    EXPECT_EQ(vertex2f(12, -2), a /= 2);
    EXPECT_EQ(vertex2f(12, -2), a);
}

TEST(Vertex2, normalize) {
    using lms::math::vertex2f;

    EXPECT_EQ(vertex2f(12.f / 13, 5.f / 13), vertex2f(12, 5).normalize());
}

TEST(Vertex2, negate) {
    using lms::math::vertex2f;

    EXPECT_EQ(vertex2f(-3, 5), vertex2f(3, -5).negate());
    EXPECT_EQ(vertex2f(1, 2), - vertex2f(-1, -2));
}

TEST(Vertex2, rotate) {
    using lms::math::vertex2i;

    EXPECT_EQ(vertex2i(0, -1), vertex2i(1, 0).rotateClockwise90deg());
    EXPECT_EQ(vertex2i(1, -1), vertex2i(1, 1).rotateClockwise90deg());
    EXPECT_EQ(vertex2i(0, 0), vertex2i(0, 0).rotateClockwise90deg());

    EXPECT_EQ(vertex2i(0, 1), vertex2i(1, 0).rotateAntiClockwise90deg());
    EXPECT_EQ(vertex2i(-1, 1), vertex2i(1, 1).rotateAntiClockwise90deg());
    EXPECT_EQ(vertex2i(0, 0), vertex2i(0, 0).rotateAntiClockwise90deg());
}
