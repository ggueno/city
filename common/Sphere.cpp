#include "Sphere.hpp"

void Sphere::build(GLfloat r, GLsizei discLat, GLsizei discLong, int normalSens ){
    GLfloat rcpLat = 1.f / discLat, rcpLong = 1.f / discLong;
    GLfloat dPhi = 2 * M_PI * rcpLat, dTheta = M_PI * rcpLong;

    std::vector<int> triangleList;
    std::vector<float> uvs;
    std::vector<float> vertices;
    std::vector<float> normals;


    // Construit l'ensemble des vertex
    for(GLsizei j = 0; j <= discLong; ++j) {
        GLfloat cosTheta = cos(-M_PI / 2 + j * dTheta);
        GLfloat sinTheta = sin(-M_PI / 2 + j * dTheta);

        for(GLsizei i = 0; i < discLat; ++i) {
            uvs.push_back(i * rcpLat);
            uvs.push_back(1.f - j * rcpLong);

            normals.push_back(normalSens * sin(i * dPhi) * cosTheta);
            normals.push_back(normalSens * sinTheta);
            normals.push_back(normalSens * cos(i * dPhi) * cosTheta);

            vertices.push_back(r*sin(i * dPhi) * cosTheta);
            vertices.push_back(r*sinTheta);
            vertices.push_back(r*cos(i * dPhi) * cosTheta);
        }
    }


    // Construit les vertex finaux en regroupant les données en triangles:
    // Pour une longitude donnée, les deux triangles formant une face sont de la forme:
    // (i, i + 1, i + discLat + 1), (i, i + discLat + 1, i + discLat)
    // avec i sur la bande correspondant à la longitude
    for(GLsizei j = 0; j < discLong; ++j) {
        //GLsizei offset = j * discLat;
        for(GLsizei i = 0; i < discLat; ++i) {

            if(i+1!=discLat){
	            triangleList.push_back(discLat*j+i);
	            triangleList.push_back(discLat*j+i+1);
	            triangleList.push_back(discLat*(j+1)+i+1);

	            triangleList.push_back(discLat*j+i);
	            triangleList.push_back(discLat*(j+1)+i+1);
	            triangleList.push_back(discLat*(j+1)+i);

        	}else{
        		triangleList.push_back(discLat*j+i);
	            triangleList.push_back(discLat*j);
	            triangleList.push_back(discLat*(j+1));

	            triangleList.push_back(discLat*j+i);
	            triangleList.push_back(discLat*(j+1));
	            triangleList.push_back(discLat*(j+1)+i);
        	}
        }
    }

    createMesh(triangleList,vertices,normals,uvs);
}
