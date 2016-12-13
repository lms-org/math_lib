#pragma once

#include <Eigen/Eigen>
#include <lms/math/interpolation.h>

namespace lms{
namespace math{
struct Pose2D{
    Pose2D():x(0),y(0),phi(0){
    }
    Pose2D(float x,float y,float phi):x(x),y(y),phi(phi),stamp(0){}
    float x;
    float y;
    float phi;
    long stamp;
};

struct CoordinateSystem2D{
    float x,y,phi;
    CoordinateSystem2D():x(0),y(0),phi(0){
    }
    CoordinateSystem2D(const Pose2D &p):x(p.x),y(p.y),phi(p.phi){
    }

    Pose2D transformTo(const Pose2D &pose){
        //create rotation matrix (passive)
        Eigen::Matrix3f transRot;
        transRot(0,0) = cos(phi);
        transRot(1,0) = sin(phi);
        transRot(0,1) = -sin(phi);
        transRot(1,1) = cos(phi);
        transRot(2,0) = x;
        transRot(2,0) = y;
        transRot(2,0) = 1;
        transRot(0,2) = 0;
        transRot(1,2) = 0;

        //rotate position
        Eigen::Vector3f v;
        v.x() = pose.x;
        v.y() = pose.y;
        v.z() = 0;
        v=transRot*v;
        Pose2D res;
        res.x = v.x();
        res.y = v.y();
        //calculate angle TODO not sure if this is right
        res.phi = pose.phi-phi;
        return res;
    }
};
class Pose2DHistory{
    Pose2D m_currentPose;
    std::vector<Pose2D> poses;
public:
    Pose2DHistory():posesMaxSize(-1){

    }
    int posesMaxSize;

    /**
     * @brief update
     * @param dx
     * @param dy
     * @param dphi drehung des Koordinatensystems
     * @param time (can be abused as id) in ms
     */
    void addPose(float x, float y, float phi, long time){
        m_currentPose.x = x;
        m_currentPose.y = y;
        m_currentPose.phi = phi;
        m_currentPose.stamp = time;
        poses.push_back(m_currentPose);
        if(posesMaxSize != -1 && (int)poses.size() > posesMaxSize){
            poses.erase(poses.begin()+1);
            //TODO remove some points in between
        }
    }
    /**
     * @brief getPose
     * @param time
     * @param pose
     * @return false if the time is before the pose or if the time is after the last pose
     */
    bool getPose(const long time,Pose2D &pose) const{
        if(poses.size() == 0 || poses[0].stamp < time)
            return false;
        for(std::size_t i = 1; i < poses.size(); i++){
            if(poses[i].stamp >= time){
                //long should fit into double
                pose.x = lms::math::linearInterpolation<double>(poses[i].stamp,poses[i].x,poses[i-1].stamp,poses[i-1].x,time);
                pose.y = lms::math::linearInterpolation<double>(poses[i].stamp,poses[i].y,poses[i-1].stamp,poses[i-1].y,time);
                pose.phi = lms::math::linearInterpolation<double>(poses[i].stamp,poses[i].phi,poses[i-1].stamp,poses[i-1].phi,time);
                return true;
            }
        }
        return false;
    }

    Pose2D currentPose() const{
        return m_currentPose;
    }
    /**
     * @brief deltaPose
     * @param time1
     * @param time2
     * @param pose
     * @return
     */
    bool deltaPose(const long time1, const long time2, Pose2D &pose){
        Pose2D pose1,pose2;
        if(!getPose(time1,pose1))
            return false;
        if(!getPose(time2,pose2))
            return false;
        pose.x = pose2.x -pose1.x;
        pose.y = pose2.y -pose1.y;
        pose.phi = pose2.phi -pose1.phi;
        pose.stamp = pose2.stamp -pose1.stamp;
        return true;
    }
    /**
     * @brief deltaPose
     * @param time
     * @param pose
     * @return
     */
    bool deltaPose(const long time, Pose2D &pose){
        Pose2D pose1;
        if(!getPose(time,pose1))
            return false;
        pose.x = currentPose().x -pose1.x;
        pose.y = currentPose().y -pose1.y;
        pose.phi = currentPose().phi -pose1.phi;
        pose.stamp = currentPose().stamp -pose1.stamp;
        return true;
    }
};

}
}
