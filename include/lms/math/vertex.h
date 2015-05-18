#ifndef LMS_MATH_VERTEX_H
#define LMS_MATH_VERTEX_H
#include <cmath>
/**
 * Simple vertex implementation.
 */
namespace lms {
namespace math {

/**
 * @brief Implementation of a 2-dimensional vector.
 */
template <typename T>
class vertex2 {
public:
    T x, y;

    vertex2() : x(0), y(0) {}

    vertex2(const T &x, const T &y) : x(x), y(y) {}

    vertex2(const vertex2<T> &v) =default;
    vertex2<T>& operator = (const vertex2<T> &v) =default;

    T slope() const {
        return y / x;
    }

    T slope(const vertex2<T>& v) const {
        return (v.y - y)/(v.x - x);
    }

    float angle() const {
        return atan2(y ,x);
    }

    float angle(const vertex2<T> &v) const {
        return atan2(v.y - y, v.x - x);
    }

    T lengthSquared() const {
        return x * x + y * y;
    }

    float length() const {
        return sqrt(lengthSquared());
    }

    /**
     * @brief distance
     * @param to
     * @return distance
     */
    T distanceSquared(const vertex2<T> &to) const {
        return (*this - to).lengthSquared();
    }

    /**
     * @brief distance2
     * @param to
     * @return squared distance
     */
    float distance(const vertex2<T> &to) const {
        return (*this - to).length();
    }

    vertex2<T>& operator += (const vertex2<T> &add) {
        this->x += add.x;
        this->y += add.y;
        return *this;
    }

    vertex2<T>& operator -= (const vertex2<T> &sub) {
        this->x -= sub.x;
        this->y -= sub.y;
        return *this;
    }

    vertex2<T>& operator *= (const T& mul) {
        this->x *= mul;
        this->y *= mul;
        return *this;
    }

    vertex2<T>& operator /= (const T& div) {
        this->x /= div;
        this->y /= div;
        return *this;
    }

    bool operator == (const vertex2<T> &v) const {
        return x == v.x && y == v.y;
    }

<<<<<<< HEAD
    float angle(const vertex2& top) const{
        return atan2(top.y()-y(),top.x()-x());
    }

    vertex2<_T> operator - (const vertex2<_T> &other) const{
        vertex2<_T> result;
        for(int i = 0; i < 2; i++) {
            result[i] = (*this)[i] - other[i];
        }
        return result;
=======
    bool operator != (const vertex2<T> &v) const {
        return ! (*this == v);
    }

    vertex2<T> operator + (const vertex2<T> &v) const {
        return vertex2<T>(x + v.x, y + v.y);
>>>>>>> 105424364118530198fec87b3a26b21a81f64d82
    }

    vertex2<T> operator - (const vertex2<T> &v) const {
        return vertex2<T>(x - v.x, y - v.y);
    }

    vertex2<T> operator * (const T &mul) const {
        return vertex2<T>(x * mul, y * mul);
    }

    vertex2<T> operator / (const T &div) const {
        return vertex2<T>(x / div, y / div);
    }
};

typedef vertex2<int>    vertex2i;
typedef vertex2<float>  vertex2f;
typedef vertex2<double> vertex2d;

}  // namespace math
}  // namespace lms

#endif /*LMS_MATH_VERTEX_H*/
