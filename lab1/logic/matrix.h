#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <QTime>

#define matrix_data_t T*
#define const_p_matrix_data_t const T*

template <class T> class Matrix
{
    int m_row;
    int m_col;

    matrix_data_t m_matr;
    T getAvgForVector( int num );

public:
    Matrix( const int row = 0,const int col = 0 );
    ~Matrix();
    Matrix( const Matrix<T> &copy );    

    Matrix<T>& operator=( const Matrix<T>& );
    Matrix<T> operator*( const Matrix<T>& ) const;
    Matrix<T> operator-( const Matrix<T>& ) const;
    Matrix<T>& operator-=(const Matrix<T>& );
    Matrix<T> operator*( const T );
    void set(const int&, const int&, const T & );
    inline const T& get(const int&, const int&) const;
    inline T& get(const int&, const int&);
    const int& getCol() const
    {
        return m_col;
    }
    const int& getRow() const
    {
        return m_row;
    }
    QString toString() const;
    void randomInitialize();
    Matrix<T> transpose();
    Matrix<T> getVector( int num );
    void normalize();

    template<class T1>
    friend std::ostream& operator<<( std::ostream& os, const Matrix<T1>& obj );

    template<class T2>
    friend std::istream& operator>>( std::istream& is, Matrix<T2>& obj );

    const_p_matrix_data_t getMatrix() const;
};


typedef double my_t;
typedef Matrix<my_t> my_matrix;
typedef QVector<my_t> my_vector;

template <class T>
Matrix<T>::Matrix(const int row, const int col)
{
    m_row = row;
    m_col = col;

    m_matr = new T [m_row * m_col];
}

template <class T>
Matrix<T>::~Matrix()
{
    delete [] m_matr;
}

template <class T>
Matrix<T>::Matrix(const Matrix<T> &copy) :
    m_row( copy.getRow() ),
    m_col( copy.getCol() )
{

    m_matr = new T [m_row * m_col];

    const_p_matrix_data_t copyMatrix = copy.getMatrix();

    for( int i = 0; i < m_row * m_col; i++ )
    {
        m_matr[i] = copyMatrix[i];
    }
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &other){

    if( this != &other )
    {
        delete [] m_matr;

        m_col = other.getCol();
        m_row = other.getRow();
        m_matr = new T [m_row * m_col];

        const_p_matrix_data_t otherMatrix = other.getMatrix();

        for( int i = 0; i < m_row * m_col; ++i )
        {
            m_matr[i] = otherMatrix[i];
        }
    }
    return *this;
}

template <typename T>
Matrix<T>  Matrix<T>::operator*(const Matrix<T>& other) const
{
    if( this->m_col == other.getRow() )
    {
        int res_col = other.getCol();
        Matrix result_matrix( m_row, res_col );

        T el = 0;        
        for( int i = 0; i < m_row; ++i )
        {
            for( int j = 0; j < res_col; ++j )
            {
                for( int k = 0; k < m_col; ++k)
                {
                    el += m_matr[i * m_col + k] * other.get(k, j);
                }
                result_matrix.get(i, j) = el;
                el = 0;
            }
        }
        return result_matrix;
    }
    else
    {
        Q_ASSERT(false);
    }
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &other) const
{
    if( other.getCol() != m_col || other.getRow() != m_row )
    {
        return *this;
    }

    Matrix<T> newMatrix(m_row, m_col);

    for( int i = 0; i < m_row; i++ )
    {
        for( int j = 0; j < m_col; j++ )
        {
            newMatrix.set(i, j, get(i, j) - other.get(i, j));
        }
    }

    return newMatrix;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other )
{
    if( other.getCol() != m_col || other.getRow() != m_row )
    {
        return *this;
    }

    for( int i = 0; i < m_row; i++ )
    {
        for( int j = 0; j < m_col; j++ )
        {
            this->set(i, j, get(i, j) - other.get(i, j));
        }
    }

    return *this;
}

template <typename T>
void Matrix<T>::set(const int &row, const int &col, const T& val){

    m_matr[row * m_col + col] = val;
}

template <typename T>
Matrix<T>  Matrix<T>::operator*(const T val)
{
    Matrix mnew( m_row, m_col );

    for( int i = 0; i < m_row; ++i)
    {
        for( int j = 0; j < m_col; ++j)
        {
            mnew.get(i, j) = m_matr[i * m_col + j] * val;
        }
    }
    return mnew;
}

template <typename T>
inline const T &Matrix<T>::get(const int &row, const int &col) const
{
    return m_matr[m_col * row + col];
}

template <typename T>
inline T& Matrix<T>::get(const int& row, const int& col)
{
    return m_matr[m_col * row + col];
}

template <typename T>
const T *Matrix<T>::getMatrix() const
{
    return m_matr;
}

template <typename T>
QString Matrix<T>::toString() const
{
    QString matrixString;
    matrixString.append("{ ");
    for( int i = 0; i < m_row; i++ )
    {
        matrixString.append("{ ");
        for( int j = 0; j < m_col; j++ )
        {
            matrixString.append(( (j != 0)?",":"") +  QString::number( m_matr[ i * m_col + j] ));
        }
        matrixString.append("}\n");
    }
    matrixString.append("}");
    return matrixString;
}

template <typename T>
void Matrix<T>::randomInitialize()
{
    qsrand(QTime::currentTime().msec());

    for( int i = 0; i < m_row; i++ )
    {
        for( int j = 0; j < m_col; j++ )
        {
            long int rand_value = rand() % 2001;
            set(i,j, T(rand_value / 1000. - 1));
        }
    }
}

template <typename T>
Matrix<T> Matrix<T>::transpose()
{
    Matrix newMatrix( m_col, m_row);

    for( int i = 0; i < m_row; i++ )
    {
        for( int j = 0; j < m_col; j++ )
        {
            newMatrix.set( j, i, m_matr[i * m_col + j] );
        }
    }

    return newMatrix;
}

template <typename T>
Matrix<T> Matrix<T>::getVector(int num)
{
    Matrix vector(1, m_col);

    for( int j = 0; j < m_col; j++ )
    {
        vector.set(0, j, m_matr[num * m_col + j]);
    }

    return vector;
}

template <typename T>
void Matrix<T>::normalize()
{
    for( int j = 0; j < m_col; j++ )
    {
        T avg = getAvgForVector(j);

        for( int i = 0; i < m_row; i++ )
        {
            set(i, j, m_matr[i * m_col + j] / avg);
        }
    }
}

template <typename T>
T Matrix<T>::getAvgForVector(int num)
{
    T sum = 0;

    for( int i = 0; i < m_row; i++ )
    {
        sum += m_matr[i * m_col + num] * m_matr[i * m_col + num];
    }

    return sqrt( sum );
}

template <typename T>
std::ostream & operator <<(std::ostream &os, const Matrix<T>& obj)
{
    os << obj.m_row << std::endl;
    os << obj.m_col << std::endl;
    for( int i = 0; i < obj.m_row; i++ )
    {
        for( int j = 0; j < obj.m_col; j++ )
        {
            os << obj.m_matr[i * obj.m_col + j] << " ";
        }
    }
    return os;
}

template <typename T>
std::istream & operator >>(std::istream &is, Matrix<T>& obj)
{
    int row, col;

    is >> row;
    is >> col;

    obj = Matrix<T>( row, col );

    for( int i = 0; i < obj.m_row; i++ )
    {
        for( int j = 0; j < obj.m_col; j++ )
        {
            T v;
            is >> v;
            obj.m_matr[i * obj.m_col + j] = v;
        }
    }

//    if( /* no valid object of T found in stream */ )
//        is.setstate(std::ios::failbit);
    return is;
}

#endif // MATRIX_H
