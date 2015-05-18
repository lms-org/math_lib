#ifndef LMS_MATH_POLYLINE_H
#define LMS_MATH_POLYLINE_H
#include <vector>
#include "lms/math/vertex.h"
#include <algorithm>
#include <functional>
namespace lms{
namespace math{

template<typename VERTEX>
class PolyLine{
    std::vector<VERTEX> m_points;
public:
    const std::vector<VERTEX>& points() const{
        return m_points;
    }
    std::vector<VERTEX>& points(){
        return m_points;
    }

    void move(VERTEX toAdd){
        for(int i = 0; i < m_points.size(); i++){
            points()[i] += toAdd;
        }
    }

    float distance(){
        float sum = 0;
        for(int i = 1; i < m_points.size(); i++){
            sum += points[i-1].distance(m_points[i]);
        }
        return sum;
    }

    void sort(std::function<bool(const VERTEX&,const VERTEX&)> sortF){
        std::sort(points().begin(), points().end(),sortF);
    }
    /**
     * @brief sortByDistance
     * @param absolue if set to true, the line will be sorted using the distance. Shortest distance will be at beginning
     * if set to false, the line will be sorted using the relative distance to the points. For example if it's a unsorted path of a line and the first point is at the beginning you will receive the line
     */
    void sortByDistance(bool absolute){
        //TODO absolute is easy
        //TODO relative may be quite hard
    }
    /**
     * @brief flip first index will be last and vise versa
     */
    void flip(){
        //TODO
    }

    PolyLine<VERTEX>& operator += (const PolyLine<VERTEX> toAdd){
        for(VERTEX v:toAdd.points()){
            this->points().push_back(v);
        }
        return *this;
    }

    PolyLine<VERTEX> operator -= (const PolyLine<VERTEX> sub){
        //TODO remote vectors that are the same
        return this;
    }
    /**
     * @brief reduce used to reduce unnecessary points. The list should be sorted before!
     * @param distanceF TODO
     */
    void reduce(std::function<bool(const VERTEX&,const VERTEX&)> distanceF){
        for(int i = 0; i < ((int)points().size()) -1;){
            //quite dirty, wouldn't work if the vertex doesn't have a distance method...
            if(distanceF(points()[i],points()[i+1])){
                points().erase(points().begin() + i+1);
            }else{
                i++;
            }
        }
    }
    /**
     * @brief reduce used to reduce unnecessary points.
     * @param distanceF returning true will remove the VERTEX
     */
    void reduce(std::function<bool(const VERTEX&)> distanceF){
        for(int i = 0; i < ((int)points().size()) -2;){
            //quite dirty, wouldn't work if the vertex doesn't have a distance method...
            if(distanceF(points()[i])){
                points().erase(points().begin() + i);
            }else{
                i++;
            }
        }
    }
    /**
     * @brief reduce used to reduce unnecessary points. The list should be sorted before!
     * @param distanceF returning true will remove the second VERTEX
     */
    void reduce(std::function<bool(const VERTEX&,const VERTEX&,const VERTEX&)> distanceF){
        for(int i = 0; i < ((int)points().size()) -2;){
            //quite dirty, wouldn't work if the vertex doesn't have a distance method...
            if(distanceF(points()[i],points()[i+1],points()[i+2])){
                points().erase(points().begin() + i+1);
            }else{
                i++;
            }
        }
    }


};

typedef PolyLine<lms::math::vertex2f> polyLine2f;
}
}
#endif /* LMS_MATH_POLYLINE_H */
