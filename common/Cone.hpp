#ifndef __CONE__
#define __CONE__

#include "Mesh.hpp"
#include <math.h>

class Cone : public Mesh{
public:
	Cone(GLfloat height, GLfloat radius, GLsizei discLat, GLsizei topDivision, Vec3D & pos) :
		Mesh(pos),
		m_height(height),
		m_radius(radius),
		m_discLat(discLat),
		m_topDivision(topDivision)
	{
		build(m_height,m_radius,m_discLat,m_topDivision);
	};
	~Cone(){};

	void build(GLfloat height, GLfloat radius, GLsizei discLat, GLsizei topDivision);

private:
	GLfloat m_height;
	GLfloat m_radius;
	GLsizei m_discLat;
	GLsizei m_topDivision;
};
#endif