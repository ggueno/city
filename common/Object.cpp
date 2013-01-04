#include "Object.hpp"



Object::Object(const std::string &name) :  m_name("test"), m_visible(true), m_shaderID(0)
{
    m_model.setIdentity();
}



Object::Object(GLuint shaderID) : m_name("object"), m_shaderID(shaderID), m_visible(true){
    m_model.setIdentity();
}

Object::~Object()
{
    m_vecMesh.clear();
}

/*copy the meshes and the shaderID of the object but does not create physic body
Indeed where to put it? not to the same positon => program will explode! */
Object::Object(const Object &object)
{
    m_model.setIdentity();
    //mat4fToIdentity(m_model);

    for(unsigned int i =0; i< object.m_vecMesh.size(); i++)
    {
        this->m_vecMesh.push_back(object.m_vecMesh[i]);
    }

    this->m_shaderID = object.m_shaderID;
    this->m_name = object.m_name + "*";
    this->m_visible = object.m_visible;
}


void Object::addMesh(Mesh* mesh)
{
    m_vecMesh.push_back(mesh);
}

//modelview = view en argument
void Object::drawObject(GLuint shaderID)
{
    if(!m_visible) return;


    for(unsigned int i=0; i<m_vecMesh.size(); i++){
        m_vecMesh[i]->drawMesh(m_model,shaderID);
        //printf("shader=%d \n",m_shaderID);
        //m_vecMesh[i]->drawMeshSimple();
    }

}

void Object::drawObject()
{
    if(!m_visible) return;

    //modelview*=m_model;

    ///glUniformMatrix4fv(glGetUniformLocation(m_vecObject[i]->getShader(), "view"), 1, GL_TRUE, view.m_value);

    for(unsigned int i=0; i<m_vecMesh.size(); i++){
        m_vecMesh[i]->drawMesh(m_model,m_shaderID);
        //printf("shader=%d \n",m_shaderID);
        //m_vecMesh[i]->drawMeshSimple();
    }

}


void Object::resetTransformation()
{
    m_model.setIdentity();
}

//Be careful: opengl => column major / Newton => row major so transpose after translate...
void Object::setMatrixModel(const Matrix & model)
{
    m_model = model;
}

void Object::translatee(float x, float y, float z)
{
    m_model.translate(x,y,z);
    // float mat[16];
    // float vecP[4] = {x,y,z,1.0};
    // translate(m_model.m_value,vecP,mat);
    // for(int i=0; i<4; ++i)
    //     for(int j=0; j<4; ++j)
    //         m_model.m_value[i*4+j]=mat[i*4+j];

}

 void Object::setPosition(float x, float y, float z)
 {
    m_model[3] = x;
    m_model[7] = y;
    m_model[11] = z;
 }

void Object::scalee(float x, float y, float z)
{
    m_model.scale(x,y,z);
}

void Object::rotatee(float angle, float x, float y, float z)
{
    m_model.rotate(angle,x,y,z);
}

void Object::setOrientation(float angle, float x, float y, float z)
{
    //Vec3D posSave(m_model[3],m_model[7], m_model[11]);
    //m_model.setIdentity();
    //m_model.rotate(angle,x,y,z);
    //m_model.translate(posSave.x, posSave.y, posSave.z);
}

