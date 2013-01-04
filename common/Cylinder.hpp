#ifndef __CYLINDER__
#define __CYLINDER__

#include "Mesh.hpp"
#include <math.h>
#include "maths.hpp"

class Cylinder : public Mesh{
public:
	Cylinder(GLfloat height, GLfloat width, GLfloat length, GLsizei discLat, GLsizei discHeight) :
		Mesh(),
		m_height(height),
        m_width(width),
		m_length(length),
		m_discLat(discLat),
		m_discHeight(discHeight)
	{
		build(m_height,m_width, m_length,m_discLat,m_discHeight);
	};
	Cylinder(GLfloat height, GLfloat width, GLfloat length, GLsizei discLat, GLsizei discHeight, Vec3D pos) :
		Mesh(pos),
		m_height(height),
        m_width(width),
		m_discLat(discLat),
		m_discHeight(discHeight)
	{
		build(m_height,m_width,m_length, m_discLat,m_discHeight);
	};
	~Cylinder(){};

	void build(GLfloat height, GLfloat radius,  GLfloat length, GLsizei discLat, GLsizei discHeight);

private:
	GLfloat m_height;
    GLfloat m_width;
	GLfloat m_length;
	GLsizei m_discLat;
	GLsizei m_discHeight;
};


class Base : public Mesh{
public:
    Base(Vec3D tL, Vec3D bL, Vec3D bR, Vec3D tR)
    {
        build(tL,bL,bR,tR);
    };

    Base(Vec3D center, float height, float width, float length)
    {
        build(center,height, width, length);
    };

    void build(Vec3D tL, Vec3D bL, Vec3D bR, Vec3D tR);
    void build(Vec3D center, float height, float width, float length);

private:

};
#endif