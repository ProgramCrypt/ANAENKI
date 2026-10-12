//----------------------------------------------------------------
//
// Author(s): McKendree Springer
// Project: ANÆNKI engine
// Purpose: This class handles functionality of 4x4 transform matrices
// Copyright © McKendree Springer
//
//----------------------------------------------------------------

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "matrix2D.h"
#include "vectorF.h"

class Transform : public Matrix2D
{
    public:
    //////// Public Functions ////////
    // Constructor
    Transform(void) {setToIdentity();} // Initiates as identity matrix by default

    // Deconstructor
    ~Transform(void);

    Vector2 operator*(const Vector2& v) const;
    
    Vector3 operator*(const Vector3& v) const;

    // Sets to identity matrix
    void setToIdentity() override;

    // Sets to a translate transform matrix
    void setToTranslate(Vector3 translation);

    // Sets to a scale transform matrix
    void setToScale(Vector3 scale);

    // Sets to a rotate transform matrix
    void setToRotateDeg(float deg);
    void setToRotateRad(float rad);

    // Returns 3D vector representing (x,y,z) coordinates
    Vector3 position();

    private:
    //////// Private Functions ////////
    
    //////// Private Variables ////////
    
};

#endif // TRANSFORM_H