#ifndef LOT_HPP
#define LOT_HPP

#include <iostream>

#include "maths.hpp"

class Lot{
public:
    Lot(Vec3D topLeft, Vec3D bottomLeft, Vec3D bottomRight, Vec3D topRight, float height):
        m_topLeft(topLeft),
        m_bottomLeft(bottomLeft),
        m_bottomRight(bottomRight),
        m_topRight(topRight),
        m_buildingHeight(height),
        m_full(false) {
            // if(m_topLeft.x > m_topRight.x){
            //     std::swap(m_topLeft,m_topRight);
            //     std::swap(m_bottomLeft,m_bottomRight);
            // }
            // if(m_bottomRight.z > m_topRight.z){
            //     std::swap(m_bottomRight,m_topRight);
            //     std::swap(m_bottomLeft,m_topLeft);
            // }

        };

    Vec3D getTopLeft(){  return m_topLeft;}
    Vec3D getTopRight(){ return m_topRight; }
    Vec3D getBottomLeft(){ return m_bottomLeft; }
    Vec3D getBottomRight(){ return m_bottomRight; }
    Vec3D getCenter(){
        return Vec3D(m_topRight.x - getWidth() / 2.0, 0.0, m_bottomRight.z - getHeight()/2.0 );
    }

    void setTopLeft(Vec3D topL){ m_topLeft = topL; }
    void setTopRight(Vec3D topR){ m_topRight = topR; }
    void setBottomLeft(Vec3D bottomL){ m_bottomLeft = bottomL; }
    void setBottomRight(Vec3D bottomR){ m_bottomRight = bottomR; }
    void setBuildingHeight(float height){ m_buildingHeight = height;}

    float getWidth(){ return fabs(m_topRight.x - m_topLeft.x); };
    float getHeight(){ return fabs(m_bottomRight.z - m_topRight.z); };
    float getBuildingHeight(){ return m_buildingHeight; }

    bool isFull(){ return m_full; }

    void print(){
        std::cout << "(" << m_topLeft.x << "," << m_topLeft.y << "," << m_topLeft.z << ")" << std::endl;
        std::cout << "(" << m_bottomLeft.x << "," << m_bottomLeft.y << "," << m_bottomLeft.z << ")" << std::endl;
        std::cout << "(" << m_bottomRight.x << "," << m_bottomRight.y << "," << m_bottomRight.z << ")" << std::endl;
        std::cout << "(" << m_topRight.x << "," << m_topRight.y << "," << m_topRight.z << ")" << std::endl;
        std::cout << std::endl;
    }

protected:
    Vec3D m_topLeft, m_topRight, m_bottomRight, m_bottomLeft;
    float m_buildingHeight;
    bool m_full;
};


#endif