#ifndef __MESH__
#define __MESH__

#include <GL/glew.h>
#include <vector>
#include <string>
#include <stdio.h>
#include "Transform.hpp"
#include "maths.hpp"
#include "LinearAlgebra.hpp"

typedef struct face2{
    int v[3];
    int vt[3];
    int vn[3];
}FaceM;

struct Material{

    Material()
    {
        Ka = 0.001;
        Kd = 1.1;
        Ks = 1.0;
        Ns = 50.0;
        texture = 0;
    }
    GLfloat Ka; //réflexions ambiante
    GLfloat Kd; //réflexions diffuse
    GLfloat Ks; //réflexions spéculaire
    GLfloat Ns;    //"lumière" qu'il "émet"
    GLuint texture;
};


class Mesh{

    public:
        Mesh();
        Mesh(Vec3D & pos);
        ~Mesh();

        /* créer un mesh texturé */
        //void createMesh(std::vector< FaceM > *faces, std::vector<GLfloat> &vertices, std::vector<GLfloat> &normals, std::vector<GLfloat> &uvs);
        void createMesh(int *faces, float * vertices, float  * normals, float * uvs);
        void createMesh(std::vector< int > & faces, std::vector<float> & vertices, std::vector<float> & normals, std::vector<float> & uvs);
        void drawMeshSimple() const;
        void initBuffers();
        /* créer un mesh pour debugger, juste des vertices liés à la suite 2 par 2 (GL_LINES)
           attention à donner le shader de debug à l'affichage*/
        //void createDebugMesh(std::vector<GLfloat> &vertices);

        void drawMesh(const Matrix & model,const int shaderID) const;
        void drawMeshInstanced(const Matrix &model,const int shaderID, const int nb) const;

        inline void setMaterial(Material* material){ m_material = material; };
        inline Material* getMaterial(){ return m_material; };
        void setTexture(GLuint id);
        inline GLuint getVaoId(){ return m_vaoId; };

    private:

        GLuint m_vaoId;          // vertex array objet id
        GLuint m_vboId;          // vertices buffer id
        GLuint m_normalsVboId;   // normals buffer id
        GLuint m_uvsVboId;       // uvs buffer id
        GLuint m_indicesVboId;   // indices buffer id
        //GLuint colorsVboId;    // colors buffer id

        GLuint m_nbVertices;
        GLuint m_nbIndices;

        Material* m_material;

        //Si appel a createDebugMesh: true
        bool m_meshDebug;

    protected:
        Vec3D m_pos;
};

#endif
