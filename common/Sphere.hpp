#ifndef __SPHERE__
#define __SPHERE__

#include "Mesh.hpp"
#include <math.h>
#include "maths.hpp"

class Sphere : public Mesh{
public:
	Sphere(GLfloat radius, GLsizei discLat, GLsizei discLong, int normalSens = -1) :
		Mesh(),
		m_radius(radius),
		m_discLat(discLat),
		m_discLong(discLong)
	{
		build(m_radius,m_discLat,m_discLong, normalSens);
	};
	Sphere(GLfloat radius, GLsizei discLat, GLsizei discLong, Vec3D pos, int normalSens = -1) :
		Mesh(pos),
		m_radius(radius),
		m_discLat(discLat),
		m_discLong(discLong)
	{
		build(m_radius,m_discLat,m_discLong, normalSens);
	};
	~Sphere(){};

	void build(GLfloat radius, GLsizei discLat, GLsizei discLong, int normalSens);

private:
	GLfloat m_radius;
	GLsizei m_discLat;
	GLsizei m_discLong;
};


#endif