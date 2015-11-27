#ifndef LMS_MATH_POLYLINE_H
#define LMS_MATH_POLYLINE_H
#include <vector>
#include "lms/math/vertex.h"
#include <algorithm>
#include <functional>
#include "lms/inheritance.h"


#ifdef USE_CEREAL
#include "lms/serializable.h"
#include "cereal/cerealizable.h"
#include "cereal/cereal.hpp"
#include "cereal/types/vector.hpp"
#endif

namespace lms{
namespace math{

template<typename VERTEX>
class PolyLine
#ifdef USE_CEREAL
    : public lms::Serializable
#endif
{
protected:
    std::vector<VERTEX> m_points;
public:
    virtual ~PolyLine() {}

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

    float length(){
        float sum = 0;
        for(int i = 1; i < m_points.size(); i++){
            sum += m_points[i-1].distance(m_points[i]);
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

    // cereal implementation
    #ifdef USE_CEREAL
        //get default interface for datamanager
        CEREAL_SERIALIZATION()

        template <class Archive>
        void serialize( Archive & archive) {
            archive(m_points);
        }
    #endif
};



class polyLine2f : public PolyLine<lms::math::vertex2f>, public virtual lms::Inheritance{
public:
    virtual bool isSubType(size_t hashcode) const override{
        (void)hashcode;
        return false;
    }
    virtual ~ polyLine2f(){}
    /**
     * @brief distance TODO
     * @param v
     * @return
     */
    float distance(const lms::math::vertex2f &v){
        if(m_points.size() == 0)
            return NAN;
        float minDistance = 0;
        if(m_points.size() == 1){
            return (m_points[0]-v).length();
        }
        for(uint i = 1; i < m_points.size(); i++){

        }
        return minDistance;
    }
    /**
     * @brief getWithDistanceBetweenPoints
     * @param distance
     * @return
     */
    polyLine2f getWithDistanceBetweenPoints(float distance)const {
        polyLine2f result;
        if(m_points.size() == 0){
            return result;
        }
        int currentIndex = 1;
        result.points().push_back(m_points[0]);//add first point
        while(true){
            lms::math::vertex2f lastPoint = result.points()[0];
            lms::math::vertex2f next = m_points[currentIndex];
            //find valid next
            while(lastPoint.distance(next) < distance){
                currentIndex++;
                if(currentIndex >= (int)m_points.size()){
                    break;
                }
                next = m_points[currentIndex];
            }
            //found valid next
            //add new point
            lms::math::vertex2f diff = next-lastPoint;
            result.points().push_back(lastPoint+diff.normalize()*distance);
        }
        return result;
    }
    /**
     * @brief moveOrthogonal
     * @param distance
     * @return empty polyLine2f if the transition is not possible
     */
    polyLine2f moveOrthogonal(float distance){
        polyLine2f result;
        //check if it's possible
        if(m_points.size() < 2){
            return result;
        }
        lms::math::vertex2f diff;
        for(int i = 1; i <(int) m_points.size(); i++){
            lms::math::vertex2f top = m_points[i];
            lms::math::vertex2f bot = m_points[i-1];
            lms::math::vertex2f diff = top-bot;
            diff = diff.rotateAntiClockwise90deg().normalize()*distance;
            result.points().push_back(bot+diff);
        }
        result.points().push_back(m_points[m_points.size()-1]+diff);
        return result;
    }
};
}  // namespace math
}  // namespace lms

#endif /* LMS_MATH_POLYLINE_H */
