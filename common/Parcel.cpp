#include "Parcel.hpp"

double frandd_a_b(double a, double b){
    return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}

void Parcel::divide(Vec3D leftCorner, float height, float width, int it){

        if( it == 0) return;

        float buildingHeight = frandd_a_b(m_buildingHeightMin, m_buildingHeightMax);

        if( height / 2.0 < m_lotMinSize || width / 2.0 < m_lotMinSize) {
            //std::cout << height<< "<" << m_lotMinSize << std::endl;
            //std::cout << width / 2.0<< "<" << m_lotMinSize << std::endl;
            m_listLots.push_back(
                new Lot(
                    Vec3D(leftCorner.x, 0.0, leftCorner.z),
                    Vec3D(leftCorner.x, 0.0, leftCorner.z+height),
                    Vec3D(leftCorner.x+width, 0.0, leftCorner.z+height),
                    Vec3D(leftCorner.x+width, 0.0, leftCorner.z),
                    buildingHeight
                )
            );
        }else{

            float r = frandd_a_b(0.3,0.7);

            Vec3D tmp1 = Vec3D(leftCorner.x+r*width, 0.0, leftCorner.z); //E

            //r = frandd_a_b(0.3,0.7);
            Vec3D tmp2 = Vec3D(tmp1.x, 0.0,tmp1.z+height);

            r = frandd_a_b(0.3,0.7);
            Vec3D tmp3 = Vec3D(leftCorner.x, 0.0, leftCorner.z+r*height);

            //r = frandd_a_b(0.3,0.7);
            Vec3D tmp4 = Vec3D(tmp3.x+width, 0.0, tmp3.z);

            //Callback of the function for the topLeft terrain
            Vec3D intersect = Vec3D(tmp1.x, 0.0, tmp3.z);

            if(it == 1){
                //Margin

                //Top left parcel
                m_listLots.push_back(
                    new Lot(
                        Vec3D(leftCorner.x, 0.0, leftCorner.z),
                        Vec3D(tmp3.x, 0.0, tmp3.z),
                        Vec3D(intersect.x, 0.0, intersect.z),
                        Vec3D(tmp1.x, 0.0, tmp1.z),
                        buildingHeight
                    )
                );


                //Top right parcel
                m_listLots.push_back(
                    new Lot(
                        Vec3D(tmp1.x, 0.0, tmp1.z),
                        Vec3D(intersect.x, 0.0, intersect.z),
                        Vec3D(tmp4.x, 0.0, tmp4.z),
                        Vec3D(leftCorner.x+width, 0.0, leftCorner.z),
                        buildingHeight
                    )
                );

                //Bottom right parcel
                m_listLots.push_back(
                    new Lot(
                        Vec3D(intersect.x,0.0, intersect.z),
                        Vec3D(tmp2.x ,0.0, tmp2.z ),
                        Vec3D(leftCorner.x + width ,0.0, leftCorner.z + height ),
                        Vec3D(tmp4.x ,0.0, tmp4.z ),
                        buildingHeight
                    )
                );

                //Bottom left parcel
                m_listLots.push_back(
                    new Lot(
                        Vec3D(tmp3.x,0.0, tmp3.z),
                        Vec3D(leftCorner.x ,0.0, leftCorner.z + height ),
                        Vec3D(tmp2.x ,0.0, tmp2.z ),
                        Vec3D(intersect.x,0.0, intersect.z),
                        buildingHeight
                    )
                );
        }

        float width1 = fabs(tmp1.x-leftCorner.x);
        float width2 = fabs(leftCorner.x+width-tmp1.x);
        float height1 = fabs(tmp3.z - leftCorner.z);
        float height2 = fabs(leftCorner.z+height-tmp3.z);

        divide(leftCorner, height1, width1, it-1); //AGIE
        divide(tmp3, height2, width1 , it-1); //GBFI
        divide(intersect, height2, width2, it-1); //IFCH
        divide(tmp1, height1, width2, it-1); //EIH
    }
}