#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix
{
    public:
    //////// Public Functions ////////
    // Constructors
    Matrix(); // sets m to 4x4 identity matrix by default
    Matrix(int rows, int cols); // will automatically set to identity matrix if rows == cols

    // Deconstructor
    ~Matrix(void);

    // Sets to identity matrix if dimensions are square
    void setToIdentity();

    // Sets value at coordinate (row, column)
    void setVal(int row, int col, float value);

    // Gets value at coordinate (row, column)
    float getVal(int row, int col) {return m[row][col];}

    // Sets to a translate matrix
    void setToTranslate(int x, int y);

    private:
    //////// Private Functions ////////
    
    //////// Private Variables ////////
    // Matrix data
    std::vector<std::vector<float>> m;

};

#endif // MATRIX_H