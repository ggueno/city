#ifndef __BUILDING__
#define __BUILDING__

#include "Object.hpp"
#include "Parcel.hpp"
#include "Cylinder.hpp"
#include "Sphere.hpp"
#include "Cone.hpp"
#include "maths.hpp"
#include <cstdlib>
#include <iostream>
#include <ctime>

class Building : public Object{
public:
	Building(GLuint shaderID);
	Building(float height, float width);
    Building(GLuint shaderID, float width, float height);
    Building(GLuint shaderID, Lot & lot);
	~Building();

	// Accesseur
	float getHeight(){ return m_height;};
	float getWidth(){ return m_width; };
	Vec3D getPosition(){ return m_position; };

    void drawObject();
    void drawObject(GLuint shaderID);

	void setPosition(Vec3D & position){ m_position = position; };
	void setWidth(float width){ m_width = width; };
	void setHeight(float height){ m_height = height; };
    void init();
	void init(Lot & lot);

    void createSimple(float width, float length, float height, bool antenna, bool roof, bool rounded,float margin);
    void createBlocky(float width, float length, float height, int nb_block);
    void createStacky(float width, float length, float height, int nb_stack, bool roof, bool antenna);
private:
	float m_height;
	float m_width;
	Vec3D m_position; //position of the building on the map
};

#endif