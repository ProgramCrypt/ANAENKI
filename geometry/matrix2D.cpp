#include "matrix2D.h"


//////// Public Functions ////////
// Constructors
// sets m to 4x4 identity matrix by default
Matrix2D::Matrix2D()
{
    m = std::vector<std::vector<float>>(4,std::vector<float>(4,0));
}
// will automatically set to identity matrix if rows == cols
Matrix2D::Matrix2D(size_t rows, size_t cols)
{
    for (int i = 0; i < rows; ++i)
    {
        std::vector<float> row(cols,0.0);
        m.push_back(row);
    }
} 

// Deconstructor
Matrix2D::~Matrix2D(void) {}

// Sets to identity matrix if dimensions are square
void Matrix2D::setToIdentity()
{
    // Checks if matrix has equal number of rows and columns
    if (m.size() == m[0].size())
    {
        for (int i = 0; i < m.size(); ++i)
        {
            for (int j = 0; j < m[0].size(); ++j)
            {
                if (i == j) m[i][j] = 1.0;
                else m[i][j] = 0.0;
            }
        }
    }
}

Matrix2D Matrix2D::operator*(const Matrix2D& other) const
{
    Matrix2D newMat(m.size(), m[0].size());

    if (m.size() == other.size()[1] && m[0].size() == other.size()[0])
    {
        for (int r = 0; r < m.size(); ++r)
        {
            for (int c = 0; c < m[0].size(); ++c)
            {
                float val = 0;

                for (int i = 0; i < m[0].size(); ++i)
                {
                    val += m[r][i] * other[i][c];
                }

                newMat[r][c] = val;
            }
        }
    }

    return newMat;
}

// Sets value at coordinate (row, column)
void Matrix2D::setVal(size_t row, size_t col, float value)
{
    // Checks if coordinate is a valid location in matrix
    if (row < m.size() && col < m[0].size())
    {
        m[row][col] = value;
    }
}

// Returns dimensions of matrix as a vector (rows, columns)
std::vector<size_t> Matrix2D::size() const
{
    std::vector<size_t> size = {m.size(), m[0].size()};
    return size;
}