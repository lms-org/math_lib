#ifndef LMS_MATH_CURVE_H
#define LMS_MATH_CURVE_H

#include <functional>
#include <vector>

namespace lms {
namespace math {

void bresenhamLine(int x0, int y0, int x1, int y1,std::function<bool(int,int)> foundPixel);
void bresenhamLine(int x0, int y0, int x1, int y1, std::vector<int> &vX, std::vector<int> &vY);

}  // namespace math
}  // namespace lms

#endif /* LMS_MATH_CURVE_H */
