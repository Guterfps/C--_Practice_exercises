
#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;

static const size_t g_num_of_rows = 5;

class Matrix
{
public:
    Matrix(size_t rows = 1, size_t cols = 1);
    ~Matrix();

    size_t *SumOfRows(size_t *result) const;
    void Print() const;
    
private:
    double **NewMatrix(size_t rows, size_t cols);
    
    size_t m_numOfRows;
    size_t m_numOfCols;
    double **m_matrix;
};


int main(void)
{
    Matrix mat(g_num_of_rows, 5);
    size_t result[g_num_of_rows] = {0};
    
    mat.SumOfRows(result);
    mat.Print();
    
    for (size_t i = 0; i < g_num_of_rows; ++i)
    {
        cout <<"sum of row: "<< i << " is: " << result[i] << endl;
    }
    
    return 0;
}

Matrix::Matrix(size_t rows, size_t cols) : 
m_numOfRows(rows), m_numOfCols(cols), m_matrix(NewMatrix(rows,cols))
{
}

Matrix::~Matrix()
{
    for (size_t i = 0; i < m_numOfRows; ++i)
    {
        delete[] m_matrix[i];
    }
    
    delete[] m_matrix;
}

double **Matrix::NewMatrix(size_t rows, size_t cols)
{
    double **newMatrix = new double*[rows];
    
    for (size_t i = 0; i < rows; ++i)
    {
        newMatrix[i] = new double[cols];
        for (size_t j = 0; j < cols; ++j)
        {
            newMatrix[i][j] = i + j;
        }
    }
    
    return newMatrix;
}

size_t *Matrix::SumOfRows(size_t *result) const
{
    for (size_t i = 0; i < m_numOfRows; ++i)
    {
        for (size_t j = 0; j < m_numOfCols; ++j)
        {
            result[i] += m_matrix[i][j];
        }
    }
    
    return result;
}

void Matrix::Print() const
{
    for (size_t i = 0; i < m_numOfRows; ++i)
    {
        for (size_t j = 0; j < m_numOfCols; ++j)
        {
            cout << m_matrix[i][j] << ", ";
        }
        cout << endl;
    }
}

