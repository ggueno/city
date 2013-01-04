#include "Cone.hpp"

void Cone::build(GLfloat height, GLfloat r, GLsizei discLat, GLsizei topDivision){
	GLfloat rcpLat = 1.f / discLat, rcpH = 1.f;
    GLfloat dPhi = 2 * M_PI * rcpLat, dH = height * rcpH;

    std::vector<int> triangleList;
    std::vector<float> uvs;
    std::vector<float> vertices;
    std::vector<float> normals;

    // Construit l'ensemble des vertex
    for(GLsizei i = 0; i < discLat; ++i) {
        uvs.push_back(i * rcpLat);
        uvs.push_back(rcpH);

        normals.push_back(sin(i * dPhi));
        normals.push_back(0.f);
        normals.push_back(cos(i * dPhi));

       	vertices.push_back(r * sin(i * dPhi)+m_pos.x);
       	vertices.push_back(0.+m_pos.y);
       	vertices.push_back(cos(i * dPhi)+m_pos.z);
    }


    uvs.push_back(0.);
    uvs.push_back(0.);

    normals.push_back(1.0f);
    normals.push_back(0.f);
    normals.push_back(0.0f);

    vertices.push_back(0.+m_pos.x);
    vertices.push_back(0.+m_pos.y);
    vertices.push_back(0.+m_pos.z);

    uvs.push_back(0.);
    uvs.push_back(0.);

    normals.push_back(1.0f);
    normals.push_back(0.f);
    normals.push_back(0.0f);

    vertices.push_back(0.+m_pos.x);
    vertices.push_back(height+m_pos.y);
    vertices.push_back(0.+m_pos.z);

    // Construit les vertex finaux en regroupant les données en triangles:
    // Pour une longitude donnée, les deux triangles formant une face sont de la forme:
     // (i, i + 1, i + discLat + 1), (i, i + discLat + 1, i + discLat)
    // avec i sur la bande correspondant à la longitude
    int top = discLat/topDivision;
    for(GLsizei j = 0; j < 2; ++j) {
        for(GLsizei i = 0; i < discLat; i+=top) {
            if(i+top!=discLat){
                triangleList.push_back(discLat+j);
                triangleList.push_back(i);
                triangleList.push_back(i+1);
        	}else{
                triangleList.push_back(discLat+j);
                triangleList.push_back(i);
                triangleList.push_back(0);
        	}
        }
    }

    createMesh(triangleList,vertices,normals,uvs);
}