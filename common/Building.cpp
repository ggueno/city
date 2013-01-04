#include "Building.hpp"

Building::Building(GLuint shaderID) : Object(shaderID), m_width(0.0f), m_height(0.0f){
	init();
}

Building::Building(GLuint shaderID, float width, float height) : Object(shaderID), m_width(width), m_height(height){
    init();
}

Building::Building(GLuint shaderID, Lot & lot) : Object(shaderID){
    init(lot);

}

Building::Building(float height, float width): Object("building"), m_height(height), m_width(width) {};

void Building::init(){
	//random width and height
	float a = 1.6;
	float b = 3.0;

    float width = rand() / float (RAND_MAX) * ((b-a) + a);
	float largeur = rand() / float (RAND_MAX) * ((b-a) + a);
    float height = rand() / float (RAND_MAX) * (10.0-2.0) + 2.0;
	int nbCote = int( rand() / float (RAND_MAX) * (360.0-4.0) + 4.0 );
    float roof = rand() / float (RAND_MAX) * ((b-a) + a);

    if(nbCote<50){
        nbCote = 4;
    }

    //  Mesh * base = new Cylinder(width, height)


    //construction de la base

    // Vec3D pos(0.0,0.0,0.0);
    // Mesh * mesh = new Cylinder(height,largeur,nbCote,4,pos);
    // m_vecMesh.push_back(mesh);

    if(roof>0.3){
        // Vec3D pos2(0.0,height,0.0);
        // Mesh * roof = new Cone(height/10,largeur,nbCote,nbCote,pos2);
        // m_vecMesh.push_back(roof);
    }
}

//modelview = view en argument
void Building::drawObject()
{
    if(!m_visible) return;

    //modelview*=m_model;

    ///glUniformMatrix4fv(glGetUniformLocation(m_vecObject[i]->getShader(), "view"), 1, GL_TRUE, view.m_value);

    // Matrix base;
    // base.setIdentity();
    // m_vecMesh[0]->drawMesh(base,m_shaderID);

    for(unsigned int i=0; i<m_vecMesh.size(); i++){
        m_vecMesh[i]->drawMesh(m_model,m_shaderID);
        //printf("shader=%d \n",m_shaderID);
        //m_vecMesh[i]->drawMeshSimple();
    }

}

void Building::drawObject(GLuint shaderID)
{
    if(!m_visible) return;

    //modelview*=m_model;

    ///glUniformMatrix4fv(glGetUniformLocation(m_vecObject[i]->getShader(), "view"), 1, GL_TRUE, view.m_value);

    // Matrix base;
    // base.setIdentity();
    // m_vecMesh[0]->drawMesh(base,shaderID);

    for(unsigned int i=0; i<m_vecMesh.size(); i++){
        m_vecMesh[i]->drawMeshInstanced(m_model,shaderID,20);
        //printf("shader=%d \n",m_shaderID);
        //m_vecMesh[i]->drawMeshSimple();
    }

}




void Building::init(Lot & l){
    float min_height = 0.6;
    float max_height = 10.0;

    float antenna_proba = 0.05;

    // Random height of the building
    float height = randomValue(min_height,max_height);

    // Get Position of the lot
    Vec3D topLeft = l.getTopLeft();
    Vec3D bottomLeft = l.getBottomLeft();
    Vec3D bottomRight = l.getBottomRight();
    Vec3D topRight = l.getTopRight();
    float lot_width = l.getWidth();
    float lot_height = l.getHeight();
    bool antenna = false;


    // has an antenna : randomly
    if(fabs(lot_width/lot_height)>0.8 && fabs(lot_width/lot_height)<1.2 )
        if(randomValue(0.,1.) < antenna_proba) antenna = true ;

    createSimple(lot_width, lot_height, height, antenna, false, false, 0.1);
}



void Building::createSimple(float width, float length, float height, bool antenna, bool roof, bool rounded,float margin){

    float base_height = 0.5;//GLOBAL VARIABLE : HAUTEUR DU SOCLE
    Mesh * base = new Base(Vec3D(0.0,0.0,0.0), base_height, width, length);
    m_vecMesh.push_back(base);

    Mesh * mesh;
    Vec3D pos(0.0,0.0,0.0);
    if(!rounded)
        mesh = new Base(Vec3D(0.0,0.0,0.0), height, width-margin, length-margin);
    else
        mesh = new Cylinder(height, width, length, 16, 1,pos);
    m_vecMesh.push_back(mesh);


    //TODO : Make roof adapatable to Base
    if(roof){
        float roof_height = 0.1;
        Vec3D pos(0.0,height,0.0);
        Mesh * roof = new Cone(height * roof_height, width-margin, 4, 4, pos);
        m_vecMesh.push_back(roof);
    }

    if(antenna){
        float antenna_height = 0.1;
        float antenna_width = 0.05;
        Vec3D pos(0.0,height,0.0);
        Mesh * antenna = new Cylinder(height * antenna_height, width * antenna_width, width * antenna_width, 4, 4, pos);
        m_vecMesh.push_back(antenna);
    }

}

void Building::createBlocky(float width, float length, float height, int nb_block){
    // for(int i=0; i<nb_block; ++i){
    //     //Mesh * building = new Base(Vec3D(x,0.0,z), height, width, length);
    //     //Mesh * building = new Base(topLeft, l.getBottomLeft(), l.getBottomRight(), l.getTopRight());
    //     //m_vecMesh.push_back(building);
    //     Vec3D pos(0.0,0.0,0.0);
    //     float x = randomValue( -width/4.0, width/4.0);
    //     float z = randomValue( -height/4.0, height/4.);
    //     // float x = 0.0;
    //     // float z = 0.0;
    //     float length = randomValue(min_block_length, lot_height);
    //     float width = randomValue(min_block_width, lot_width);

    //     //if(length2>lot_height/2) std::swap(length2,width)
    //     Mesh * mesh;
    //     if(randomValue(0.0,2.0)>1.0)
    //         mesh = new Base(Vec3D(x,0.0,z), height2, width2, length2);
    //     else{
    //         width2 = std::min(width2, height2) / 2.0;
    //         mesh = new Cylinder(height2,width2,width2,16,1,Vec3D(x,0.0,z));
    //             Vec3D pos2(0.0,height2,0.0);
    //             //Mesh * roof = new Cone(height2/10,width2,16,16,pos2);
    //             //m_vecMesh.push_back(roof);
    //     }
    //     m_vecMesh.push_back(mesh);
    // }
}

void Building::createStacky(float width, float length, float height, int nb_stack, bool roof, bool antenna){

}