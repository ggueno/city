#ifndef __OBJECT__
#define __OBJECT__


#include "Transform.hpp"
#include "maths.hpp"
#include "LinearAlgebra.hpp"
#include "Mesh.hpp"


#include <string>
#include <stdio.h>

class Object{

    public:
        Object(const std::string &name = "object");
        Object(GLuint shaderID);
        ~Object();
        Object(const Object &object);

        void addMesh(Mesh* mesh);
        void drawObject();
        void drawObject(GLuint shaderID, int nb = 1);

        inline void setName(const std::string &name){ m_name = name; };
        inline bool isVisible(){ return m_visible; };
        inline void setVisible(bool visible){ m_visible = visible; };
        inline const std::string& getName(){ return m_name; };
        inline void setShader(GLuint shader){ m_shaderID = shader; };
        inline GLuint getShader(){ return m_shaderID; };

        void resetTransformation();
        void setMatrixModel(const Matrix &model);
        void setPosition(float x, float y, float z);
        void setOrientation(float angle, float x, float y, float z);
        void translatee(float x, float y, float z);
        void scalee(float x, float y, float z);
        void rotatee(float angle, float x, float y, float z);
        //inline Vec3D getPosition(){ return Vec3D(m_model[3],m_model[7], m_model[11]); };

        std::vector<Mesh*> m_vecMesh;

    protected:

        //peut servir a faire des contrôles...
        std::string m_name;
        bool m_visible;

        Matrix m_model;

        GLuint m_shaderID;

};

#endif
