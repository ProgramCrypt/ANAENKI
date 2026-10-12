//----------------------------------------------------------------
//
// Author(s): McKendree Springer
// Project: ANÆNKI engine
// Purpose: This class handles functionality of 4x4 transform matrices
// Copyright © McKendree Springer
//
//----------------------------------------------------------------

#include "transform.h"



// Deconstructor
Transform::~Transform(void) {}

// Sets to identity matrix
void Transform::setToIdentity()
{
    for (int i = 0; i < rows(); ++i)
    {
        for (int j = 0; j < columns(); ++j)
        {
            if (i == j) setVal(i, j, 1.0);
            else setVal(i, j, 0.0);
        }
    }
}

Vector2 Transform::operator*(const Vector2& v) const
{
    Vector2 newVec;

    newVec.x = (*this)[0][0]*v.x + (*this)[0][1]*v.y;
    newVec.y = (*this)[1][0]*v.x + (*this)[1][1]*v.y;

	return newVec;
}
    
Vector3 Transform::operator*(const Vector3& v) const
{
    Vector3 newVec;

    newVec.x = (*this)[0][0]*v.x + (*this)[0][1]*v.y + (*this)[0][2]*v.z;
    newVec.y = (*this)[1][0]*v.x + (*this)[1][1]*v.y + (*this)[1][2]*v.z;
    newVec.z = (*this)[2][0]*v.x + (*this)[2][1]*v.y + (*this)[2][2]*v.z;

	return newVec;
}

// Sets to a translate transform matrix
void Transform::setToTranslate(Vector3 translation)
{
    setToIdentity();
    setVal(0,3,translation.x);
    setVal(1,3,translation.y);
    setVal(2,3,translation.z);
}

// Sets to a scale transform matrix
void Transform::setToScale(Vector3 scale)
{
    setToIdentity();
    setVal(0,0,scale.x);
    setVal(1,1,scale.y);
    setVal(2,2,scale.z);
}

// Sets to a rotate transform matrix
void Transform::setToRotateDeg(float deg)
{
    float angle = deg * 180/3.1415926;
}
void Transform::setToRotateRad(float rad)
{

}

// Returns 3D vector representing (x,y,z) coordinates
Vector3 Transform::position()
{

}