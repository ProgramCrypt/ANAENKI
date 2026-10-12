//----------------------------------------------------------------
//
// Author(s): McKendree Springer
// Project: ANÆNKI engine
// Purpose: This class handles functionality of (1D) float vectors.
// Copyright © McKendree Springer
//
//----------------------------------------------------------------

#ifndef VECTORF_H
#define VECTORF_H

#include <vector>


/*class VectorF
{
    public:
    //////// Public Functions ////////
    // Constructors
    VectorF() {v = std::vector<float>(3,0.0);}                             // defaults to 3D vector (0,0,0)
    VectorF(size_t size) {v = std::vector<float>(size,0.0);}               // sets number of vector elements to 'size', all with zero values
    VectorF(size_t size, float val) {v = std::vector<float>(size,val);}    // sets number of vector elements to 'size' and all element values to 'val'

    // Deconstructor
    ~VectorF() {}

    float& operator[](size_t pos) {return v[pos];}

    // Sets elemt value to 'val' at position 'pos'
    void setValue(size_t pos, float val) {v[pos] = val;}

    size_t size() {return v.size();}

    private:
    //////// Private Functions ////////

    //////// Private Variables ////////
    std::vector<float> v;
};*/

// A 2-element float vector
struct Vector2 {
    float x = 0;
    float y = 0;
};

// A 3-element float vector
struct Vector3 {
    float x = 0;
    float y = 0;
    float z = 0;
};

// A 4-element float vector
struct Vector4 {
    float x = 0;
    float y = 0;
    float z = 0;
    float w = 0;
};

#endif      // VECTORF_H
