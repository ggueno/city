#ifndef __MATHS__
#define __MATHS__

#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <stdlib.h>
#include <math.h>

class Vec3D
{
   public:
      Vec3D ();
      Vec3D (float fX,float fY, float fZ);
      virtual ~Vec3D();



      Vec3D(const Vec3D & v);
      Vec3D(const Vec3D & from,const Vec3D & to);

      Vec3D & operator= (const Vec3D & v);
      Vec3D & operator+= (const Vec3D & v);
      Vec3D operator+ (const Vec3D & v) const;

      Vec3D & operator-= (const Vec3D & v);
      Vec3D operator- (const Vec3D & v) const;

      Vec3D & operator*= (const float & a);
      Vec3D operator* (const float & a)const;

      Vec3D & operator/= (const float & a);
      Vec3D operator/ (const float & a)const;

      Vec3D crossProduct(const Vec3D & v)const;
      float length()const;
      Vec3D & normalize();

      void SetCoordinates(const float &fX, const float &fY, const float& fZ);
      void display();
      //float &operator[](unsigned int i);

      float x, y, z;
};

///########################################################################################//

class Matrix{

    public:
        Matrix();
        Matrix(const float *value);
        Matrix(const Matrix &matrix);
        ~Matrix();

        void setZero();
        void setIdentity();
        void print() const;

        void operator*=(const Matrix &mat);
        Matrix operator*(const Matrix &mat);
        float &operator[](unsigned int i);

        void translate(float x, float y, float z);
        void scale(float x, float y, float z);
        void rotate(float angle, float x, float y, float z);

        void transpose();

        float m_value[16];
};

void calculatePerspective(Matrix &matrix, float angle, float ratio, float near, float far);

///### fonctions ajoutees #####///

void getInverseGenericMatrix(Matrix& A, Matrix& B);

GLfloat dotProduct(GLfloat * a, GLfloat * b);

GLfloat getNorm(GLfloat * vec);

void multMatrixToPoint(GLfloat * pos, Matrix mat);

GLfloat scalarTriple(GLfloat * a, GLfloat * b, GLfloat *c);

void vectorProduct (GLfloat * a, GLfloat * b, GLfloat * result);

//TO DO : Templatiser et mettre dans maths
float randomValue(float a, float b);

#endif
