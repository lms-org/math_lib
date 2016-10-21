#ifndef LMS_MATH_VERTEX_H
#define LMS_MATH_VERTEX_H
#include <cmath>
#include <iostream>
#include "math.h"

#include "lms/serializable.h"
#include "cereal/cerealizable.h"
#include "cereal/cereal.hpp"

namespace lms {
namespace math {

/**
 * @brief Implementation of a 2-dimensional vector.
 */
template <typename T>
class vertex2: public lms::Serializable
{
public:
    virtual ~vertex2() {}

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
    template<typename C>
    explicit operator C(){
        return C(x,y);
    }

    vertex2<T> rotate(float angle){
        return vertex2<T>(x * cos(angle) - y * sin(angle),x * sin(angle) + y * cos(angle));
    }

    T slope(const vertex2<T>& v) const {
        return (v.y - y)/(v.x - x);
    }

    float angle() const {
        return atan2(y ,x);
    }

    /**
     * @brief angleBetween
     * @param v
     * @return value between 0 and PI?
     */
    float angleBetween(const vertex2<T> &v) const {
        float value = (*this * v) / length() / v.length();
        if(value > 1)
            value = 1;
        if(value < -1)
            value = -1;
        return acos(value);
    }

    bool left(const vertex2<T> &v){
        float orient = x * v.y - y * v.x; //crossproduct
        return orient >0;

    }

    /**
      TODO
     * @brief angleBetweenWithOrientation
     * @param v
     * @return value between 0 and 2*PI?
     */
    float angleBetweenWithOrientation(const vertex2<T> &v) const {
        float orient = x * v.y - y * v.x; //crossproduct
        float angle = angleBetween(v);
        if(orient < 0){
           angle = angle + M_PI;
        }
        return angle;
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

    /**
     * @brief minimum_distance
     * @param v first point of the line
     * @param w second point of the line
     * @param p
     * @param onTheSegment between 0 for first point, 1 for second point
     * @return
     */
    static float minimum_distance(vertex2<T> v, vertex2<T> w, vertex2<T> p, float &onTheSegment) {
        // Return minimum distance between line segment vw and point p
        const float l2 = v.distanceSquared(w);  // i.e. |w-v|^2 -  avoid a sqrt
        if (l2 == 0.0) return p.distance(v);   // v == w case
        // Consider the line extending the segment, parameterized as v + t (w - v).
        // We find projection of point p onto the line.
        // It falls where t = [(p-v) . (w-v)] / |w-v|^2
        const float t = dot(p - v, w - v) / l2;
        if (t < 0.0) return p.distance(v);       // Beyond the 'v' end of the segment
        else if (t > 1.0) return p.distance(w);  // Beyond the 'w' end of the segment
        const vertex2<T> projection = v + t * (w - v);  // Projection falls on the segment
        onTheSegment = t;
        return p.distance(projection);
    }


    static float minimum_distance(vertex2<T> v, vertex2<T> w, vertex2<T> p) {
        float dummy;
        return minimum_distance(v,w,p,dummy);
    }
    /**
     * @brief side
     * @param v point on the line
     * @param w point on the line
     * @param p the point to check
     * @return  If the formula is equal to 0, the points are colinear. If the line is horizontal, then this returns true if the point is above the line.
     * Taken from: http://stackoverflow.com/questions/1560492/how-to-tell-whether-a-point-is-to-the-right-or-left-side-of-a-line
     */
    static T side(vertex2<T> v,vertex2<T> w, vertex2<T> p){
        return sgn<T>(w.x - v.x)*(p.y - v.y) - (w.y - v.y)*(p.x - v.x);
    }

    /**
     * @brief cross the cross-product in 2D
     * @return
     */
    static T cross(vertex2<T> a,vertex2<T> b){
        return (b.x-a.y)*(a.x-b.y);
    }

    // cereal implementation
    //get default interface for datamanager
    CEREAL_SERIALIZATION()

    //cereal methods
    template<class Archive>
    void serialize(Archive & archive) {
        archive (x, y);
    }
};

template<typename T>
std::ostream& operator<< (std::ostream& os, const vertex2<T> &v) {
    return os << v.x << ", " << v.y;
}

typedef vertex2<int>    vertex2i;
typedef vertex2<float>  vertex2f;
typedef vertex2<double> vertex2d;
/**
 * @brief distanceLinePoint, calculate distance of M from the line connecting P and Q
 * lambda = 0, if the orthogonal line from PQ to M goes through P
 * lambda = 1, if the orthogonal line from PQ to M goes through Q
 * lambda  [0, ... , 1] inbetween
 * @param P
 * @param Q
 * @param M
 * @param dst
 * @param lambda
 */
inline void distanceLinePoint(lms::math::vertex2f P, lms::math::vertex2f Q, lms::math::vertex2f M, float *dst, float *lambda){
    //calculate distance of M from the line connecting P and Q
    //lambda = 0, if the orthogonal line from PQ to M goes through P
    //lambda = 1, if the orthogonal line from PQ to M goes through Q
    //lambda  [0, ... , 1] inbetween

    lms::math::vertex2f V = Q - P;

    *lambda = - (V.x*(P.x-M.x) + V.y*(P.y-M.y))/(V.x*V.x + V.y*V.y);
    lms::math::vertex2f S = P + V*(*lambda);

    *dst = sqrt((M.x-S.x)*(M.x-S.x) + (M.y-S.y)*(M.y-S.y));
}

}  // namespace math
}  // namespace lms

#endif /*LMS_MATH_VERTEX_H*/
