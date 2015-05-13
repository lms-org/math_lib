#ifndef LMS_MATH_MATH_H
#define LMS_MATH_MATH_H

namespace lms {
namespace math {
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}
/**
 * @brief limitAngle_0_2PI set the angle in the range from 0 to 2PI
 */
float limitAngle_0_2PI(float angle);
/**
 * @brief limitAngle_nPI_PI set the angle in the range from -PI to PI
 */
float limitAngle_nPI_PI(float angle);

}
}
#endif
