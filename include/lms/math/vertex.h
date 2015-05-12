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

    float distance(const vertex<_DIM,_T> to)const{
        float sum = 0;
        for(int i = 0; i < _DIM; i++){
            sum += pow((*this)[i]-to[i],2);
        }
        return pow(sum,0.5);
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

};

typedef vertex2<int>    vertex2i;
typedef vertex<3, int>    vertex3i;
typedef vertex2<float>  vertex2f;
typedef vertex<3, double> vertex3d;
typedef vertex<3, float>  vertex3f;

}
}

#endif /*LMS_MATH_VERTEX_H*/
