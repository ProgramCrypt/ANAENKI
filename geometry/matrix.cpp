#include "matrix.h"


//////// Public Functions ////////
// Constructors
// sets m to 4x4 identity matrix by default
Matrix::Matrix()
{
    m = std::vector<std::vector<float>>(4,std::vector<float>(4,0));
}
// will automatically set to identity matrix if rows == cols
Matrix::Matrix(int rows, int cols)
{
    for (int i = 0; i < rows; ++i)
    {
        std::vector<float> row(cols,0);
        m.push_back(row);
    }
} 

// Deconstructor
Matrix::~Matrix(void) {}

// Sets to identity matrix if dimensions are square
void Matrix::setToIdentity()
{
    // Checks if matrix has equal number of rows and columns
    if (m.size() == m[0].size())
    {
        for (int i = 0; i < m.size(); ++i)
        {
            for (int j = 0; j < m[0].size(); ++j)
            {
                if (i == j) m[i][j] = 1;
                else m[i][j] = 0;
            }
        }
    }
}

// Sets value at coordinate (row, column)
void Matrix::setVal(int row, int col, float value)
{
    // Checks if coordinate is a valid location in matrix
    if (row < m.size() && col < m[0].size())
    {
        m[row][col] = value;
    }
}

// Sets to a translate matrix
void Matrix::setToTranslate(int x, int y)
{

}