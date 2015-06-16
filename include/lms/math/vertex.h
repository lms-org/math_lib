#ifndef LMS_MATH_VERTEX_H
#define LMS_MATH_VERTEX_H
#include <cmath>
#include <iostream>

#ifdef USE_CEREAL
#include "lms/serializable.h"
#include "cereal/cerealizable.h"
#include "cereal/cereal.hpp"
#endif

namespace lms {
namespace math {

/**
 * @brief Implementation of a 2-dimensional vector.
 */
template <typename T>
class vertex2
#ifdef USE_CEREAL
    : public lms::Serializable
#endif
{
public:
    T x, y;

    vertex2() : x(0), y(0) {}

    vertex2(const T &x, const T &y) : x(x), y(y) {}

    vertex2(const vertex2<T> &v) =default;
    vertex2<T>& operator = (const vertex2<T> &v) =default;

    template<typename U>
    explicit vertex2(const vertex2<U> &v) : x(T(v.x)), y(T(v.y)) {}

    T slope() const {
        return y / x;
    }

    T slope(const vertex2<T>& v) const {
        return (v.y - y)/(v.x - x);
    }

    float angle() const {
        return atan2(y ,x);
    }

    float angleBetween(const vertex2<T> &v) const {
        return acos((*this * v) / length() / v.length());
    }

    /**
     * @brief Compute the squared length of the vector.
     */
    T lengthSquared() const {
        return (*this) * (*this);
    }

    /**
     * @brief Compute the length of the vector.
     */
    float length() const {
        return sqrt(lengthSquared());
    }

    /**
     * @brief Compute the squared distance between this vertex and the
     * parameter.
     */
    T distanceSquared(const vertex2<T> &to) const {
        return (*this - to).lengthSquared();
    }

    /**
     * @brief Compute the distance between this vertex and the parameter.
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

    bool operator != (const vertex2<T> &v) const {
        return ! (*this == v);
    }

    vertex2<T> operator + (const vertex2<T> &v) const {
        return vertex2<T>(x + v.x, y + v.y);
    }

    vertex2<T> operator - (const vertex2<T> &v) const {
        return vertex2<T>(x - v.x, y - v.y);
    }

    /**
     * @brief Scale the vector
     */
    vertex2<T> operator * (const T &mul) const {
        return vertex2<T>(x * mul, y * mul);
    }

    /**
     * @brief Scale the vector
     */
    vertex2<T> operator / (const T &div) const {
        return vertex2<T>(x / div, y / div);
    }

    /**
     * @brief Scalar product
     */
    T operator * (const vertex2<T> &v) const {
        return x * v.x + y * v.y;
    }

    /**
     * @brief Normalize the vector to length 1.
     */
    vertex2<T> normalize() const {
        return (*this) / length();
    }

    /**
     * @brief Invert x and y components. The returned vector points to
     * the opposite direction.
     */
    vertex2<T> negate() const {
        return (*this) * (-1);
    }

    vertex2<T> operator - () const {
        return negate();
    }

    vertex2<T> rotateClockwise90deg() const {
        return vertex2<T>(y, -x);
    }

    vertex2<T> rotateAntiClockwise90deg() const {
        return vertex2<T>(-y, x);
    }

    // cereal implementation
    #ifdef USE_CEREAL
        //get default interface for datamanager
        CEREAL_SERIALIZATION()

        //cereal methods
        template<class Archive>
        void save(Archive & archive) const {
            archive (x, y);
        }

        template<class Archive>
        void load(Archive & archive) {
            T x, y;

            archive (x, y);
        }
    #endif
};

template<typename T>
std::ostream& operator<< (std::ostream& os, const vertex2<T> &v) {
    return os << v.x << ", " << v.y;
}

typedef vertex2<int>    vertex2i;
typedef vertex2<float>  vertex2f;
typedef vertex2<double> vertex2d;

}  // namespace math
}  // namespace lms

#endif /*LMS_MATH_VERTEX_H*/
