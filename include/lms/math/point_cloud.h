#ifndef LMS_MATH_POINT_CLOUD_H
#define LMS_MATH_POINT_CLOUD_H

#include <vector>

#include "lms/math/vertex.h"

namespace lms {
namespace math {

template <typename V>
class PointCloud {
   public:
    const std::vector<V>& points() const { return m_points; }
    std::vector<V>& points() { return m_points; }

    void clear() { m_points.clear(); }
    typename std::vector<V>::size_type size() const { return m_points.size(); }

   private:
    std::vector<V> m_points;
};

using PointCloud2f = PointCloud<vertex2f>;

}  // namespace math
}  // namespace lms

#endif  // LMS_MATH_POINT_CLOUD_H
