#ifndef LMS_MATH_INTERPOLATION_H
#define LMS_MATH_INTERPOLATION_H

namespace lms {
namespace math {

/**
 * @brief Compute the linear interpolation of (x0, y0) and
 * (x1, y1) at point x. Returns the result in parameter y.
 *
 * @return true if interpolation was successful, false if x1 - x0 == 0.
 *
 * http://en.wikipedia.org/wiki/Linear_interpolation
 */
template<typename T>
T linearInterpolation(T x0, T y0, T x1, T y1, T x) {
    const T dx = x1 - x0;

    if(dx == 0) {
        return y0;
    } else {
        return y0 + (y1 - y0) * (x - x0) / dx;
    }
}



}  // namespace math
}  // namespace lms

#endif /* LMS_MATH_INTERPOLATION_H */
