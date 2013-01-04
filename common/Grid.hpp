#ifndef GRID_HPP
#define GRID_HPP

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "maths.hpp"

#include "Lot.hpp"
#include "Parcel.hpp"

enum BuildingType{ CIRCULAR, FROM_ORIGIN, RANDOM };

class Grid {
public:
    Grid(){}
    Grid(Vec3D leftCorner, float height, float width,int iteration = 3, float parcel_min_size = 1.0, float margin = 1.0);

    std::vector<Vec3D> getListofNodes(){ return listNodes; }
    std::vector<Parcel *> getListofParcels(){ return listParcels; }

    //subdivides a rectangle in order to create roads
    // We link 4 Vec3Ds 2 by 2 : the first 2 ones form the vertical road
    //                           the last 2 ones form the horizontal road
    void createRoads(Vec3D leftCorner, float height, float width, int it);
    void initDrawGrid();
    Lot * getOneLot();

protected:
    float m_parcel_min_size;
    float m_margin;
    size_t indiceFull;

    std::vector<Vec3D> listNodes;
    std::vector<Parcel * > listParcels;
    float m_width, m_height;
};

#endif
