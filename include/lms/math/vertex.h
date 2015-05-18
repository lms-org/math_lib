#ifndef LMS_MATH_VERTEX_H
#define LMS_MATH_VERTEX_H
#include <cmath>
/**
 * Simple vertex implementation.
 */
namespace lms{
namespace math{

template <int _DIM, typename _T>
class vertex : public std::array<_T, _DIM>  {
public:
    vertex<_DIM,_T>& operator += (const vertex<_DIM,_T> &add){
        for(int i = 0; i < _DIM; i++){
            (*this)[i]+=add[i];
        }
        return *this;
    }

    vertex<_DIM,_T>& operator * (_T mul){
        for(int i = 0; i < _DIM; i++){
            (*this)[i]=(*this)[i]*mul;
        }
        return *this;
    }

    bool operator == (const vertex<_DIM,_T> v){
        for(int i = 0; i < _DIM; i++){
            if((*this)[i]!=v[i])
                return false;
        }
        return true;
    }
    /**
     * @brief distance
     * @param to
     * @return distance
     */
    _T distance(const vertex<_DIM,_T> to)const{
        float sum = 0;
        for(int i = 0; i < _DIM; i++){
            sum += pow((*this)[i]-to[i],2);
        }
        return pow(sum,0.5);
    }
    /**
     * @brief distance2
     * @param to
     * @return squared distance
     */
    _T distance2(const vertex<_DIM,_T> to)const{
        float sum = 0;
        for(int i = 0; i < _DIM; i++){
            sum += pow((*this)[i]-to[i],2);
        }
        return sum;
    }
};

template <typename _T>
class vertex2 : public vertex<2, _T> {
public:
    vertex2() {}

    vertex2(_T x, _T y) {
        (*this)[0] = x;
        (*this)[1] = y;
    }
    const _T& x() const{
        return (*this)[0];
    }
    const _T& y() const{
        return (*this)[1];
    }

    _T& x(){
        return (*this)[0];
    }
    _T& y(){
        return (*this)[1];
    }

    _T slope() const{
        return y()/x();
    }

    _T slope(const vertex2& v) const{
        return (v.y()-y())/(v.x()-x());
    }
    float angle() const{
        return atan2(y(),x());
    }
    float angle(const vertex2& top) const{
        //TODO Bullshit, we should go for eigen
        return atan2(top.y()-y(),top.x()-x());
    }

    vertex2<_T> operator - (const vertex2<_T> &other) const{
        vertex2<_T> result;
        for(int i = 0; i < 2; i++) {
            result[i] = (*this)[i] - other[i];
        }
        return result;
    }

    float length() const{
        float sum = 0;
        sum += (*this)[0] * (*this)[0];
        sum += (*this)[1] * (*this)[1];
        return sqrt(sum);
    }

    vertex2<_T> operator / (_T val) {
        vertex2<_T> result;
        result[0] = (*this)[0] / val;
        result[1] = (*this)[1] / val;
        return result;
    }

    vertex2<_T> operator + (const vertex2<_T> &v) {
        vertex2<_T> result;
        result[0] = (*this)[0] + v[0];
        result[1] = (*this)[1] + v[1];
        return result;
    }
};

typedef vertex2<int>    vertex2i;
typedef vertex<3, int>    vertex3i;
typedef vertex2<float>  vertex2f;
typedef vertex<3, double> vertex3d;
typedef vertex<3, float>  vertex3f;



}
}

#endif /*LMS_MATH_VERTEX_H*/
