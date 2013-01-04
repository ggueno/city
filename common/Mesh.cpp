#include "Mesh.hpp"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

Mesh::Mesh()
{
    m_nbVertices=0;
    m_nbIndices=0;
    m_meshDebug = false;

    m_pos.x = 0.0f;
    m_pos.y = 0.0f;
    m_pos.z = 0.0f;

    initBuffers();
}

void Mesh::initBuffers(){
    /* Creation of ids for the buffers on GPU, We store them in the structure for clarity
     Creates a VAO id to handle the vao for objectTr */
    glGenVertexArrays(1, &(m_vaoId));

    // Creates a VBO id for a VBO to store the vertices
    glGenBuffers(1, &(m_vboId));

    // Creates a VBO id for a VBO to store the normals
    glGenBuffers(1, &(m_normalsVboId));
    // Creates a VBO id for a VBO to store the colors
    //glGenBuffers(1, &(this->colorsVboId));

    // Creates a VBO id for a VBO to store the uv coordinates (for textures)
    glGenBuffers(1, &(m_uvsVboId));

    // Creates a VBO id for a VBO to store the indices of the vertices
    glGenBuffers(1, &(m_indicesVboId));
}

Mesh::Mesh(Vec3D & pos)
{
    m_nbVertices=0;
    m_nbIndices=0;
    m_meshDebug = false;

    m_pos.x = pos.x;
    m_pos.y = pos.y;
    m_pos.z = pos.z;

    initBuffers();
}


Mesh::~Mesh()
{
    // Cleans by deleting the buffers
    glDeleteBuffers(1, &(m_vboId));
    glDeleteBuffers(1, &(m_normalsVboId));
    //glDeleteBuffers(1, &(this->colorsVboId));
    glDeleteBuffers(1, &(m_uvsVboId));
    glDeleteBuffers(1, &(m_indicesVboId));

    ///glDeleteVertexArrays(1, &(m_vaoId));
}

void Mesh::setTexture(GLuint id){
    m_material->texture = id;
}

void Mesh::createMesh(std::vector< int > & faces, std::vector<float> & vertices, std::vector<float> & normals, std::vector<float> & uvs){
    m_nbIndices = faces.size();

    glBindVertexArray(m_vaoId);

    // Bind indices and upload data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesVboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size()*sizeof(int), &faces[0], GL_STATIC_DRAW);


    // Bind vertices and upload data
    glBindBuffer(GL_ARRAY_BUFFER, this->m_vboId);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*3, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);

    if(normals.size()>0){
        // Bind normals and upload data
        glBindBuffer(GL_ARRAY_BUFFER, this->m_normalsVboId);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*3, (void*)0);
        glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(float), &normals[0], GL_STATIC_DRAW);
    }

    if(uvs.size()>0){// Bind uv coords and upload data
        glBindBuffer(GL_ARRAY_BUFFER, this->m_uvsVboId);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*2, (void*)0);
        glBufferData(GL_ARRAY_BUFFER, uvs.size()*sizeof(float), &uvs[0], GL_STATIC_DRAW);

        glBindVertexArray(0);
    }
}


void Mesh::drawMeshSimple() const{
    glBindVertexArray(this->m_vaoId);
    glDrawElements(GL_TRIANGLES,this->m_nbIndices, GL_UNSIGNED_INT, 0);
}

void Mesh::drawMesh(const Matrix &model,const int shaderID) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "Object"), 1, 0,  model.m_value);
    glBindVertexArray(this->m_vaoId);
    glDrawElements(GL_TRIANGLES,this->m_nbIndices, GL_UNSIGNED_INT, 0);
}

void Mesh::drawMeshInstanced(const Matrix &model,const int shaderID, const int nb) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "Object"), 1, 0,  model.m_value);
    glBindVertexArray(this->m_vaoId);
    glDrawElementsInstanced(GL_TRIANGLES,this->m_nbIndices, GL_UNSIGNED_INT, 0, nb);
}

