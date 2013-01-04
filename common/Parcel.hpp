#ifndef PARCEL_HPP
#define PARCEL_HPP

#include <iostream>
#include <vector>

#include "maths.hpp"
#include "Lot.hpp"

class Parcel{
public:
    Parcel(Vec3D topLeft, Vec3D bottomLeft, Vec3D bottomRight, Vec3D topRight):
        m_topLeft(topLeft),
        m_bottomLeft(bottomLeft),
        m_bottomRight(bottomRight),
        m_topRight(topRight),
        m_full(false),
        m_lotMinSize(1.0),
        m_indiceEmpty(0) {};

    Parcel(Vec3D topLeft, Vec3D bottomLeft, Vec3D bottomRight, Vec3D topRight, float heightMax, float heightMin):
        m_topLeft(topLeft),
        m_bottomLeft(bottomLeft),
        m_bottomRight(bottomRight),
        m_topRight(topRight),
        m_buildingHeightMax(heightMax),
        m_buildingHeightMin(heightMin),
        m_full(false),
        m_lotMinSize(1.0),
        m_indiceEmpty(0)
        {};

    Vec3D getTopLeft(){  return m_topLeft;}
    Vec3D getTopRight(){ return m_topRight; }
    Vec3D getBottomLeft(){ return m_bottomLeft; }
    Vec3D getBottomRight(){ return m_bottomRight; }
    bool isFull(){ return m_full; }

    void setTopLeft(Vec3D topL){ m_topLeft = topL; }
    void setTopRight(Vec3D topR){ m_topRight = topR; }
    void setBottomLeft(Vec3D bottomL){ m_bottomLeft = bottomL; }
    void setBottomRight(Vec3D bottomR){ m_bottomRight = bottomR; }

    float getWidth(){ return fabs(m_topRight.x - m_topLeft.x); };
    float getHeight(){ return fabs(m_bottomRight.z - m_topRight.z); };

    void print(){
        std::cout << "(" << m_topLeft.x << "," << m_topLeft.y << "," << m_topLeft.z << ")" << std::endl;
        std::cout << "(" << m_bottomLeft.x << "," << m_bottomLeft.y << "," << m_bottomLeft.z << ")" << std::endl;
        std::cout << "(" << m_bottomRight.x << "," << m_bottomRight.y << "," << m_bottomRight.z << ")" << std::endl;
        std::cout << "(" << m_topRight.x << "," << m_topRight.y << "," << m_topRight.z << ")" << std::endl;
        std::cout << std::endl;
    }

    void divide(Vec3D leftCorner, float height, float width, int it);
    void autoDivision(){
        divide(m_topLeft, getHeight(), getWidth(),4);
    }

    Lot * getEmptyLot(){
        if(m_full==true){
            return NULL;
        }
        m_indiceEmpty++;
        if(m_indiceEmpty == m_listLots.size()) m_full = true;
        //on suppose que lot va être rempli ce qui n'est pas forcément vrai
        return m_listLots[m_indiceEmpty-1];
    }
protected:

    Vec3D m_topLeft, m_topRight, m_bottomRight, m_bottomLeft;
    float m_buildingHeightMax;
    float m_buildingHeightMin;
    float m_lotMinSize;
    float m_full;
    int m_indiceEmpty;

public:
    std::vector<Lot *> m_listLots;

};

#endif