#include "maths.hpp"

#include <iostream>
#include <string.h>
#include <math.h>
#include <assert.h>

///######################################################################################//

void calculatePerspective(Matrix &matrix, float angle, float ratio, float near, float far)
{
    // Création de la matrice de projection
    Matrix projection(NULL);

    // Équation f
    float f = 1 / tan((angle / 2) * M_PI / 180);

    // Remplissage des valeurs de la matrice
    projection[0] = f / ratio;
    projection[5] = f;

    projection[10] = (near + far) / (near - far);
    projection[11] = (2 * near * far) / (near - far);

    projection[14] = -1;


    matrix*=projection;
}


///#################################### VEC3D ##################################################//

Vec3D::Vec3D () : x (0.0f), y (0.0f), z (0.0f)
{
   // do nothing
}

Vec3D::Vec3D (float fX, float fY, float fZ): x (fX), y (fY), z (fZ)
{
   // do nothing
}

Vec3D::~Vec3D()
{
   // do nothing
}

Vec3D::Vec3D(const Vec3D & v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

Vec3D::Vec3D(const Vec3D & from,const Vec3D & to)
{
    x = to.x - from.x;
    y = to.y - from.y;
    z = to.z - from.z;
}

Vec3D & Vec3D::operator= (const Vec3D & v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

Vec3D & Vec3D::operator+= (const Vec3D & v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vec3D Vec3D::operator+ (const Vec3D & v) const
{
    Vec3D t = *this;
    t += v;
    return t;
}

Vec3D & Vec3D::operator-= (const Vec3D & v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vec3D Vec3D::operator- (const Vec3D & v) const
{
    Vec3D t = *this;
    t -= v;
    return t;
}

Vec3D & Vec3D::operator*= (const float & a)
{
    x *= a;
    y *= a;
    z *= a;
    return *this;
}

Vec3D Vec3D::operator* (const float & a)const
{
    Vec3D t = *this;
    t *= a;
    return t;
}

Vec3D operator* (const float a,const Vec3D & v)
{
    return Vec3D(v.x*a,v.y*a,v.z*a);
}

Vec3D & Vec3D::operator/= (const float & a)
{
    x /= a;
    y /= a;
    z /= a;
    return *this;
}

Vec3D Vec3D::operator/ (const float & a)const
{
    Vec3D t = *this;
    t /= a;
    return t;
}

Vec3D Vec3D::crossProduct(const Vec3D & v)const
{
    Vec3D t;
    t.x = y*v.z - z*v.y;
    t.y = z*v.x - x*v.z;
    t.z = x*v.y - y*v.x;
    return t;
}

float Vec3D::length()const
{
    return sqrt( x*x + y*y + z*z);
}

Vec3D & Vec3D::normalize()
{
    float norm = length();
    //if(norm!=0.0)
    (*this)/=norm;
    return (*this);
}

void Vec3D::SetCoordinates (const float &fX, const float &fY, const float &fZ)
{
   x = fX;
   y = fY;
   z = fZ;
}

void Vec3D::display()
{
    std::cout <<"   ==>" << x << " | "<< y << " | "<< z << std::endl;
}


///#################################### MATRIX ##########################################################//

Matrix::Matrix()
{
    setIdentity();
}

Matrix::~Matrix()
{
}

Matrix::Matrix(const float *value)
{
    if(value != NULL)
    {
        std::copy(value, value + 16, m_value);
		//memcpy(this->m_value, value, 16 * sizeof(float) );
    }else{
        setZero();
    }
}

Matrix::Matrix(const Matrix &matrix)
{
    std::copy(matrix.m_value, matrix.m_value + 16, m_value);
}

void Matrix::setZero() {
    std::fill(m_value, m_value + 16, 0.0f);
}

void Matrix::setIdentity() {
    setZero();
    m_value[0] = 1.;
    m_value[5] = 1.;
    m_value[10] = 1.;
    m_value[15] = 1.;
}

void Matrix::print() const
{
    for(int i = 0; i < 16; ++i)
    {
        if(i%4==0) std::cout << std::endl;
        std::cout << m_value[i] << " ";
    }
    std::cout << std::endl;
}

void Matrix::operator*=(const Matrix &mat)
{
    Matrix result(NULL);

    // Addition des multiplications
    for(int k = 0; k < 4; ++k)
    {
        for(int j = 0; j < 4; ++j)
        {
            for(int i = 0; i < 4; ++i)
                result.m_value[4 * j + k] += m_value[4 * j + i] * mat.m_value[4 * i + k];
        }
    }

    // On copie le résultat dans la première matrice
    std::copy(result.m_value, result.m_value + 16, m_value);
}

Matrix Matrix::operator*(const Matrix &mat)
{
    Matrix result(NULL);

    // Addition des multiplications
    for(int k = 0; k < 4; ++k)
    {
        for(int j = 0; j < 4; ++j)
        {
            for(int i = 0; i < 4; ++i)
                result.m_value[4 * j + k] += m_value[4 * j + i] * mat.m_value[4 * i + k];
        }
    }
    return result;
}

float& Matrix::operator[](unsigned int i)
{
    assert(i<16);
    return m_value[i];
}

void Matrix::translate(float x, float y, float z)
{
    Matrix translation;

    translation[3] = x;
    translation[7] = y;
    translation[11] = z;

    translation.transpose();

    *this*=(translation);
}

void Matrix::scale(float x, float y, float z)
{
    Matrix scale;

    scale[0] = x;
    scale[5] = y;
    scale[10] = z;
    scale[15] = 1.0;

    scale.transpose();

    *this*=(scale);
}

void Matrix::transpose()
{
    std::swap(m_value[1], m_value[4]);
    std::swap(m_value[2], m_value[8]);
    std::swap(m_value[3], m_value[12]);
    std::swap(m_value[6], m_value[9]);
    std::swap(m_value[7], m_value[13]);
    std::swap(m_value[11], m_value[14]);
}

void Matrix::rotate(float angle, float x, float y, float z)
{
    Matrix rotation(NULL);

    // Conversion de l'angle de degrés vers radians
    angle = angle * M_PI / 180;

    Vec3D axe(x, y, z);
    axe.normalize();

    rotation[0] = axe.x*axe.x * (1 - cos(angle)) + cos(angle);
    rotation[1] = axe.x*axe.y * (1 - cos(angle)) - axe.z*sin(angle);
    rotation[2] = axe.x*axe.z * (1 - cos(angle)) + axe.y*sin(angle);

    rotation[4] = axe.x*axe.y * (1 - cos(angle)) + axe.z*sin(angle);
    rotation[5] = axe.y*axe.y * (1 - cos(angle)) + cos(angle);
    rotation[6] = axe.y*axe.z * (1 - cos(angle)) - axe.x*sin(angle);

    rotation[8] = axe.x*axe.z * (1 - cos(angle)) - axe.y*sin(angle);
    rotation[9] = axe.y*axe.z * (1 - cos(angle)) + axe.x*sin(angle);
    rotation[10] = axe.z*axe.z * (1 - cos(angle)) + cos(angle);

    rotation[15] = 1.0;

    rotation.transpose();

    *this*=(rotation);
}


///#### fonctions ajoutées ####/////

// Expensive matrix inversion
void getInverseGenericMatrix(Matrix&  A, Matrix& B)
{
	B[0]  =  A[5]*A[10]*A[15] - A[5]*A[14]*A[11] - A[6]*A[9]*A[15] + A[6]*A[13]*A[11] + A[7]*A[9]*A[14] - A[7]*A[13]*A[10];
	B[1]  = -A[1]*A[10]*A[15] + A[1]*A[14]*A[11] + A[2]*A[9]*A[15] - A[2]*A[13]*A[11] - A[3]*A[9]*A[14] + A[3]*A[13]*A[10];
	B[2]  =  A[1]*A[6]*A[15]  - A[1]*A[14]*A[7]  - A[2]*A[5]*A[15] + A[2]*A[13]*A[7]  + A[3]*A[5]*A[14] - A[3]*A[13]*A[6];
	B[3]  = -A[1]*A[6]*A[11]  + A[1]*A[10]*A[7]  + A[2]*A[5]*A[11] - A[2]*A[9]*A[7]   - A[3]*A[5]*A[10] + A[3]*A[9]*A[6];
	B[4]  = -A[4]*A[10]*A[15] + A[4]*A[14]*A[11] + A[6]*A[8]*A[15] - A[6]*A[12]*A[11] - A[7]*A[8]*A[14] + A[7]*A[12]*A[10];
	B[5]  =  A[0]*A[10]*A[15] - A[0]*A[14]*A[11] - A[2]*A[8]*A[15] + A[2]*A[12]*A[11] + A[3]*A[8]*A[14] - A[3]*A[12]*A[10];
	B[6]  = -A[0]*A[6]*A[15]  + A[0]*A[14]*A[7]  + A[2]*A[4]*A[15] - A[2]*A[12]*A[7]  - A[3]*A[4]*A[14] + A[3]*A[12]*A[6];
	B[7]  =  A[0]*A[6]*A[11]  - A[0]*A[10]*A[7]  - A[2]*A[4]*A[11] + A[2]*A[8]*A[7]   + A[3]*A[4]*A[10] - A[3]*A[8]*A[6];
	B[8]  =  A[4]*A[9]*A[15]  - A[4]*A[13]*A[11] - A[5]*A[8]*A[15] + A[5]*A[12]*A[11] + A[7]*A[8]*A[13] - A[7]*A[12]*A[9];
	B[9]  = -A[0]*A[9]*A[15]  + A[0]*A[13]*A[11] + A[1]*A[8]*A[15] - A[1]*A[12]*A[11] - A[3]*A[8]*A[13] + A[3]*A[12]*A[9];
	B[10] =  A[0]*A[5]*A[15]  - A[0]*A[13]*A[7]  - A[1]*A[4]*A[15] + A[1]*A[12]*A[7]  + A[3]*A[4]*A[13] - A[3]*A[12]*A[5];
	B[11] = -A[0]*A[5]*A[11]  + A[0]*A[9]*A[7]   + A[1]*A[4]*A[11] - A[1]*A[8]*A[7]   - A[3]*A[4]*A[9]  + A[3]*A[8]*A[5];
	B[12] = -A[4]*A[9]*A[14]  + A[4]*A[13]*A[10] + A[5]*A[8]*A[14] - A[5]*A[12]*A[10] - A[6]*A[8]*A[13] + A[6]*A[12]*A[9];
	B[13] =  A[0]*A[9]*A[14]  - A[0]*A[13]*A[10] - A[1]*A[8]*A[14] + A[1]*A[12]*A[10] + A[2]*A[8]*A[13] - A[2]*A[12]*A[9];
	B[14] = -A[0]*A[5]*A[14]  + A[0]*A[13]*A[6]  + A[1]*A[4]*A[14] - A[1]*A[12]*A[6]  - A[2]*A[4]*A[13] + A[2]*A[12]*A[5];
	B[15] =  A[0]*A[5]*A[10]  - A[0]*A[9]*A[6]   - A[1]*A[4]*A[10] + A[1]*A[8]*A[6]   + A[2]*A[4]*A[9]  - A[2]*A[8]*A[5];

	float det = A[0]*B[0] + A[4]*B[1] + A[8]*B[2] + A[12]*B[3];
	for (unsigned int i=0; i<16; ++i)
	    B[i]=B[i]/det;
}


// Returns the dot product between a and b
GLfloat dotProduct(GLfloat * a, GLfloat * b)
{
    GLfloat result=0.0;
    for (GLuint iCoord=0 ; iCoord<3 ; iCoord++)
    {
        result+=a[iCoord]*b[iCoord];
    }
    return result;
}

GLfloat getNorm(GLfloat * vec){

    return sqrtf(dotProduct(vec,vec));

}


// Multiplies a matrix to a point/vector
void multMatrixToPoint(GLfloat * pos, Matrix mat)
{
    float newPos[4];
    newPos[0]=pos[0]*mat[0]+pos[1]*mat[4]+pos[2]*mat[8] +pos[3]*mat[12];
    newPos[1]=pos[0]*mat[1]+pos[1]*mat[5]+pos[2]*mat[9] +pos[3]*mat[13];
    newPos[2]=pos[0]*mat[2]+pos[1]*mat[6]+pos[2]*mat[10]+pos[3]*mat[14];
    newPos[3]=pos[0]*mat[3]+pos[1]*mat[7]+pos[2]*mat[11]+pos[3]*mat[15];
    pos[0]=newPos[0];
    pos[1]=newPos[1];
    pos[2]=newPos[2];
    if (pos[3]!=0.0)
    {
        pos[0]/=newPos[3];
        pos[1]/=newPos[3];
        pos[2]/=newPos[3];
        pos[3]/=newPos[3];
    }
}


// Returns the scalar triple product between a, b and c
GLfloat scalarTriple(GLfloat * a, GLfloat * b, GLfloat *c)
{
    GLfloat result[4];
    vectorProduct(b,c,result);
    return dotProduct(a, result);
}


// To get the vector product
void vectorProduct (GLfloat * a, GLfloat * b, GLfloat * result)
{
	result[0]=a[1]*b[2] - a[2]*b[1];
	result[1]=a[2]*b[0] - a[0]*b[2];
	result[2]=a[0]*b[1] - a[1]*b[0];


}

float randomValue(float a, float b){
    return rand() / float (RAND_MAX) * ((b-a) + a);
}
