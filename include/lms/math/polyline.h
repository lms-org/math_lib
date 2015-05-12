#ifndef LMS_MATH_POLYLINE_H
#define LMS_MATH_POLYLINE_H
#include <vector>
#include "lms/math/vertex.h"
namespace lms{
namespace math{

template<typename VERTEX>
class PolyLine{
private:
    std::vector<VERTEX> m_points;
public:
    const std::vector<VERTEX>& points() const{
        return m_points;
    }
    std::vector<VERTEX>& points(){
        return m_points;
    }

    float distance(){
        float sum = 0;
        for(int i = 1; i < m_points.size(); i++){
            sum += points[i-1].distance(m_points[i]);
        }
        return sum;
    }
};
typedef PolyLine<lms::math::vertex2f> polyLine2f;
}
}
#endif /* LMS_MATH_POLYLINE_H */
