#include "Grid.hpp"

//computes a random float between a and b
double frand_a_b(double a, double b){
    return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}

Grid::Grid(Vec3D leftCorner, float height, float width, int iteration,
    float parcel_min_size, float margin):
    m_width(width),
    m_height(height),
    m_parcel_min_size(parcel_min_size),
    m_margin(margin)
    {
    //Init 1st Big rectangle to be divided
    listNodes.push_back(leftCorner); //leftUpCorner
    listNodes.push_back(Vec3D(leftCorner.x, 0.0,leftCorner.z+height));   //leftDownCorner
    listNodes.push_back(Vec3D(leftCorner.x+width, 0.0, leftCorner.z+height)); //rightDownCorner
    listNodes.push_back(Vec3D(leftCorner.x+width, 0.0, leftCorner.z)); //rightUpCorner

    indiceFull = 0;
    createRoads(leftCorner, height,width,iteration);
    initDrawGrid();
}

void Grid::createRoads(Vec3D leftCorner, float height, float width, int it){

    if( it == 0) return;


    // hauteur aléatoire en fonction de la proximité du centre(0,0)
    float hauteurMin;
    float hauteurMax;


    if( height / 2.0 < m_parcel_min_size || width / 2.0 < m_parcel_min_size) {

        hauteurMin = (((m_width / 2.0) - abs(leftCorner.x) + (m_height / 2.0) - abs(leftCorner.y))/ (m_width + m_height)) * 15;
        hauteurMax = hauteurMin * 1.2;
        listParcels.push_back(
            new Parcel(
                Vec3D(leftCorner.x+m_margin, 0.0, leftCorner.z+m_margin),
                Vec3D(leftCorner.x+m_margin, 0.0, leftCorner.z-m_margin+height),
                Vec3D(leftCorner.x-m_margin+width, 0.0, leftCorner.z-m_margin+height),
                Vec3D(leftCorner.x-m_margin+width, 0.0, leftCorner.z+m_margin),
                hauteurMax,
                hauteurMin
            )
        );
    }else{

        float r = frand_a_b(0.3,0.8);
        //r = 0.5f;
        //std::cout<<r<<std::endl;
        //Random Vec3Ds on width
        Vec3D tmp1 = Vec3D(leftCorner.x+r*width, 0.0, leftCorner.z); //E
        listNodes.push_back(tmp1);

        //r = frand_a_b(0.3,0.8);
        //Vec3D tmp2 = Vec3D(leftCorner.x+r*width, 0.0,tmp1.z+height);
        Vec3D tmp2 = Vec3D(tmp1.x, 0.0,tmp1.z+height);
        listNodes.push_back(tmp2);//F

        //Random Vec3Ds on height
        r = frand_a_b(0.3,0.8);
        //r = 0.3f;
        Vec3D tmp3 = Vec3D(leftCorner.x, 0.0, leftCorner.z+r*height);
        //Vec3D tmp3 = Vec3D
        listNodes.push_back(tmp3);//G

        //r = frand_a_b(0.3,0.8);
        //Vec3D tmp4 = Vec3D(tmp3.x+width, 0.0, leftCorner.z+r*height);
        Vec3D tmp4 = Vec3D(tmp3.x+width, 0.0, tmp3.z);
        listNodes.push_back(tmp4); //H

        //Callback of the function for the topLeft terrain
        Vec3D intersect = Vec3D(tmp1.x, 0.0, tmp3.z);


        if(it == 1){
            //Margin

            hauteurMin = (((m_width / 2.0) - abs(leftCorner.x) + (m_height / 2.0) - abs(leftCorner.y))/ (m_width + m_height)) * 15;
            hauteurMax = hauteurMin * 3.0;
            //Top left parcel
            listParcels.push_back(
                new Parcel(
                    Vec3D(leftCorner.x+m_margin, 0.0, leftCorner.z+m_margin),
                    Vec3D(tmp3.x+m_margin, 0.0, tmp3.z-m_margin),
                    Vec3D(intersect.x-m_margin, 0.0, intersect.z-m_margin),
                    Vec3D(tmp1.x-m_margin, 0.0, tmp1.z+m_margin),
                    hauteurMax,
                    hauteurMin
                )
            );


            hauteurMin = (((m_width / 2.0) - abs(tmp1.x) + (m_height / 2.0) - abs(tmp1.y))/ (m_width + m_height)) * 15;
            hauteurMax = hauteurMin * 2.0;
            //Top right parcel
            listParcels.push_back(
                new Parcel(
                    Vec3D(tmp1.x+m_margin, 0.0, tmp1.z+m_margin),
                    Vec3D(intersect.x+m_margin, 0.0, intersect.z-m_margin),
                    Vec3D(tmp4.x-m_margin, 0.0, tmp4.z-m_margin),
                    Vec3D(leftCorner.x+width-m_margin, 0.0, leftCorner.z+m_margin),
                    hauteurMax,
                    hauteurMin
                )
            );


            hauteurMin = (((m_width / 2.0) - abs(intersect.x) + (m_height / 2.0) - abs(intersect.y))/ (m_width + m_height)) * 15;
            hauteurMax = hauteurMin * 2.0;
            //Bottom right parcel
            listParcels.push_back(
                new Parcel(
                    Vec3D(intersect.x+m_margin,0.0, intersect.z+m_margin),
                    Vec3D(tmp2.x + m_margin,0.0, tmp2.z - m_margin),
                    Vec3D(leftCorner.x + width -m_margin,0.0, leftCorner.z + height - m_margin),
                    Vec3D(tmp4.x - m_margin,0.0, tmp4.z + m_margin),
                    hauteurMax,
                    hauteurMin
                )
            );

            //Bottom left parcel
            hauteurMin = (((m_width / 2.0) - abs(tmp3.x) + (m_height / 2.0) - abs(tmp3.y))/ (m_width + m_height)) * 15;
            hauteurMax = hauteurMin * 2.0;
            listParcels.push_back(
                new Parcel(
                    Vec3D(tmp3.x+m_margin,0.0, tmp3.z+m_margin),
                    Vec3D(leftCorner.x + m_margin,0.0, leftCorner.z + height - m_margin),
                    Vec3D(tmp2.x -m_margin,0.0, tmp2.z - m_margin),
                    Vec3D(intersect.x-m_margin,0.0, intersect.z+m_margin),
                    hauteurMax,
                    hauteurMin
                )
            );

        }


        float width1 = fabs(tmp1.x-leftCorner.x);
        float width2 = fabs(leftCorner.x+width-tmp1.x);
        float height1 = fabs(tmp3.z - leftCorner.z);
        float height2 = fabs(leftCorner.z+height-tmp3.z);

        createRoads(leftCorner, height1, width1, it-1); //AGIE
        createRoads(tmp3, height2, width1 , it-1); //GBFI
        createRoads(intersect, height2, width2, it-1); //IFCH
        createRoads(tmp1, height1, width2, it-1); //EIHD

    }
}


void Grid::initDrawGrid(){

    //on pourrait aussi definir ça directement dans le constructeur mais je sais pas si c'est terrible
    // ceci permet de ne pas déclarer les FBO à chaque fois ....

    std::vector<int> triangleList;
    std::vector<float> uvs;
    std::vector<float> vertices;
    std::vector<float> normals;

    std::cout << listParcels.size() << std::endl;

    for(size_t i = 0; i<listParcels.size();i++){
        //listParcels[i]->initBuffers();

        listParcels[i]->autoDivision();

        vertices.clear();
        triangleList.clear();
        uvs.clear();
        normals.clear();

        vertices.push_back(listParcels[i]->getTopLeft().x);
        vertices.push_back(listParcels[i]->getTopLeft().y);
        vertices.push_back(listParcels[i]->getTopLeft().z);

        vertices.push_back(listParcels[i]->getBottomLeft().x);
        vertices.push_back(listParcels[i]->getBottomLeft().y);
        vertices.push_back(listParcels[i]->getBottomLeft().z);

        vertices.push_back(listParcels[i]->getBottomRight().x);
        vertices.push_back(listParcels[i]->getBottomRight().y);
        vertices.push_back(listParcels[i]->getBottomRight().z);

        vertices.push_back(listParcels[i]->getTopRight().x);
        vertices.push_back(listParcels[i]->getTopRight().y);
        vertices.push_back(listParcels[i]->getTopRight().z);


        //listParcels[i].print();


        //uvs
        uvs.push_back(0.0);
        uvs.push_back(0.0);

        uvs.push_back(1.0);
        uvs.push_back(0.0);

        uvs.push_back(1.0);
        uvs.push_back(1.0);

        uvs.push_back(0.0);
        uvs.push_back(1.0);

        //normals
        normals.push_back(0.0f);
        normals.push_back(1.f);
        normals.push_back(0.0f);

        normals.push_back(0.0f);
        normals.push_back(1.f);
        normals.push_back(0.0f);

        normals.push_back(0.0f);
        normals.push_back(1.f);
        normals.push_back(0.0f);

        normals.push_back(0.0f);
        normals.push_back(1.f);
        normals.push_back(0.0f);


        triangleList.push_back(0); //A
        triangleList.push_back(1); //B
        triangleList.push_back(3); //D

        triangleList.push_back(1); //B
        triangleList.push_back(2); //C
        triangleList.push_back(3); //D

        //listParcels[i]->createMesh(triangleList, vertices, normals, uvs);
    }
}


Lot * Grid::getOneLot(){

    if(indiceFull+1 == listParcels.size()) return NULL;
    // For the moment its random
    size_t i = indiceFull;
    if(listParcels[i]->isFull()){
        indiceFull++;
    }

    if(indiceFull == listParcels.size()) return NULL;
    return listParcels[indiceFull]->getEmptyLot();
}