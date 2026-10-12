//----------------------------------------------------------------
//
// Author(s): McKendree Springer
// Project: ANÆNKI engine
// Purpose: This class handles general functionality of 2D matrices
// Copyright © McKendree Springer
//
//----------------------------------------------------------------

#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <vector>

class Matrix2D
{
    public:
    //////// Public Functions ////////
    // Constructors
    Matrix2D(); // sets m to 4x4 identity matrix by default
    Matrix2D(size_t rows, size_t cols); // will automatically set to identity matrix if rows == cols

    // Deconstructor
    ~Matrix2D(void);

    // [] operator returns row (as vector<float>) specified by argument
    std::vector<float>& operator[](size_t row) {return m[row];}
    std::vector<float> operator[](size_t row) const {return m[row];}

    Matrix2D operator*(const Matrix2D& other) const;

    // Sets to identity matrix if dimensions are square
    virtual void setToIdentity();

    // Sets value at coordinate (row, column)
    void setVal(size_t row, size_t col, float value);

    // Gets value at coordinate (row, column)
    float getVal(size_t row, size_t col) const {return m[row][col];}

    // Returns dimensions of matrix as a vector (rows, columns)
    std::vector<size_t> size() const;

    // Returns number of rows
    size_t rows() const {return m.size();}

    // Returns number of columns
    size_t columns() const {return m[0].size();}

    private:
    //////// Private Functions ////////
    
    //////// Private Variables ////////
    // Matrix data
    std::vector<std::vector<float>> m;

};

#endif // MATRIX2D_H