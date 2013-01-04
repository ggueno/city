#include "Cylinder.hpp"

void Cylinder::build(GLfloat height, GLfloat r, GLfloat length, GLsizei discLat, GLsizei discHeight){
	GLfloat rcpLat = 1.f / discLat, rcpH = 1.f / discHeight;
    GLfloat dPhi = 2 * M_PI * rcpLat, dH = height * rcpH;

    std::vector<int> triangleList;
    std::vector<float> uvs;
    std::vector<float> vertices;
    std::vector<float> normals;

    int jump = -1;
    if(randomValue(0.0,1.0)>0.8){
        jump = discLat/4.0;
    }

    // Construit l'ensemble des vertex
    for(GLsizei j = 0; j <= discHeight; ++j) {
        for(GLsizei i = 0; i <= discLat; ++i) {
            uvs.push_back(i * rcpLat);
            uvs.push_back(j * rcpH);

            normals.push_back(sin(i * dPhi));
            normals.push_back(0.f);
            normals.push_back(cos(i * dPhi));

           	vertices.push_back(r * sin(i * dPhi) + m_pos.x);
           	vertices.push_back(j * dH + m_pos.y);
           	vertices.push_back(r * cos(i * dPhi) + m_pos.z);

            if(jump!=-1)
                if( 2==i || i==discLat/2){
                    i+=jump;
                    if(i >= discLat) i = discLat-2;
                }
        }
    }


    int nbLat = vertices.size()/(3*(discHeight+1));
    // Construit les vertex finaux en regroupant les données en triangles:
    // Pour une longitude donnée, les deux triangles formant une face sont de la forme:
    // (i, i + 1, i + discLat + 1), (i, i + discLat + 1, i + discLat)
    // avec i sur la bande correspondant à la longitude
    for(GLsizei j = 0; j < discHeight; ++j) {
        //GLsizei offset = j * discLat;
        for(GLsizei i = 0; i < nbLat; ++i) {
        	triangleList.push_back(nbLat*j+i);
            triangleList.push_back(nbLat*j+i+1);
            triangleList.push_back(nbLat*(j+1)+i+1);

            triangleList.push_back(nbLat*j+i);
            triangleList.push_back(nbLat*(j+1)+i+1);
            triangleList.push_back(nbLat*(j+1)+i);
        }
    }


    int size = vertices.size() / 3;

    for(GLsizei j = 0; j <= discHeight; ++j) {
        uvs.push_back(0);
        uvs.push_back(0);

        normals.push_back(0.f);
        normals.push_back(1.f);
        normals.push_back(0.f);

        vertices.push_back(0.0f + m_pos.x);
        vertices.push_back(j*dH + m_pos.y);
        vertices.push_back(0.0f + m_pos.z);
    }

    for(GLsizei j = 0; j <= discHeight; ++j) {
        //GLsizei offset = j * discLat;
        for(GLsizei i = 0; i <= nbLat; ++i) {
            triangleList.push_back(size + j );
            triangleList.push_back(nbLat*j + i);
            triangleList.push_back(nbLat*j + i + 1);
        }
    }

    createMesh(triangleList,vertices,normals,uvs);
}


void Base::build(Vec3D tL, Vec3D bL, Vec3D bR, Vec3D tR){
    std::vector<int> triangleList;
    std::vector<float> uvs;
    std::vector<float> vertices;
    std::vector<float> normals;

    for(size_t i=0; i<2; i++){
        vertices.push_back(tL.x);
        vertices.push_back(tL.y+i*0.5);
        vertices.push_back(tL.z);

        vertices.push_back(bL.x);
        vertices.push_back(bL.y+i*0.5);
        vertices.push_back(bL.z);

        vertices.push_back(bR.x);
        vertices.push_back(bR.y+i*0.5);
        vertices.push_back(bR.z);

        vertices.push_back(tR.x);
        vertices.push_back(tR.y+i*0.5);
        vertices.push_back(tR.z);

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
    }


    for(size_t i=0; i<2; i++){
        triangleList.push_back(0+i*4); //A
        triangleList.push_back(1+i*4); //B
        triangleList.push_back(3+i*4);

        triangleList.push_back(1+i*4); //B
        triangleList.push_back(2+i*4); //C
        triangleList.push_back(3+i*4); //D
    }

    for(size_t i=0; i<4; i++){

            triangleList.push_back(i);
            triangleList.push_back(i+4);
        if(i+1!=4)
            triangleList.push_back(i+4+1);
        else
            triangleList.push_back(i+1);

            triangleList.push_back(i);
        if(i+1!=4){
            triangleList.push_back(i+1);
            triangleList.push_back(i+4+1);
        }else{
            triangleList.push_back(0);
            triangleList.push_back(i+1);
        }


    }

    createMesh(triangleList, vertices, normals, uvs);

}





void Base::build(Vec3D center, float height, float width, float length){

    Vec3D tL = Vec3D(center.x-width/2.0, 0.0,center.z+length/2.0);
    Vec3D tR = Vec3D(center.x+width/2.0, 0.0,center.z+length/2.0);
    Vec3D bL = Vec3D(center.x-width/2.0, 0.0,center.z-length/2.0);
    Vec3D bR = Vec3D(center.x+width/2.0, 0.0,center.z-length/2.0);

    int cube_triangleCount = 12;
    int   cube_triangleList[] = {0, 1, 2, 2, 1, 3, 4, 5, 6, 6, 5, 7, 8, 9, 10, 10, 9, 11, 12, 13, 14, 14, 13, 15, 16, 17, 18, 19, 17, 20, 21, 22, 23, 24, 25, 26, };
    float cube_uvs[] = {0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f,  1.f, 0.f,  1.f, 1.f,  0.f, 1.f,  1.f, 1.f,  0.f, 0.f, 0.f, 0.f, 1.f, 1.f,  1.f, 0.f,  };
    float cube_vertices[] = {-0.5, -0.5, 0.5, 0.5, -0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, 0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, 0.5, -0.5, 0.5, 0.5 };
    float cube_normals[] = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, };
    
    std::vector<int> triangleList(cube_triangleList, cube_triangleList + sizeof cube_triangleList / sizeof (int));
    std::vector<float> uvs(cube_uvs, cube_uvs + sizeof cube_uvs / sizeof (float));
    std::vector<float> normals(cube_normals, cube_normals + sizeof cube_normals / sizeof (float));
    std::vector<float> vertices(cube_vertices, cube_vertices + sizeof cube_vertices / sizeof (float));

    std::cout << "triangleList.size()=" << triangleList.size() << std::endl;
    
    createMesh(triangleList, vertices, normals, uvs);

}