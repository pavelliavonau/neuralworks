#ifndef MATRIX_H
#define MATRIX_H
#include <QVector>
#include <QPair>
#include <iostream>
#include "stdlib.h"
#include <cmath>
#include <QTime>

#define matrix_data_t QVector< QVector<T> >

template <class T> class Matrix
{
    int row;
    int col;

    matrix_data_t matr;
    T getAvgForVector( int num );

public:
    Matrix( const int row = 0,const int col = 0 );

    Matrix( const Matrix<T> &copy );

    Matrix<T>& operator=( const Matrix<T>& );
    Matrix<T> operator*( const Matrix<T>& ) const;
    Matrix<T> operator-( const Matrix<T>& ) const;
    Matrix<T> operator*( const T );
    void set( const int, const int, const T );
    T get(int,int) const;
    int getCol() const;
    int getRow() const;
    QString toString() const;
    void randomInitialize();
    Matrix<T> transpose();
    Matrix<T> getVector( int num );
    void normalize();

    template<class T1>
    friend std::ostream& operator<<( std::ostream& os, const Matrix<T1>& obj );

    template<class T2>
    friend std::istream& operator>>( std::istream& is, Matrix<T2>& obj );

    T& operator[]( QPair< int, int >& );
    const T& operator[]( const QPair< int, int >& ) const;
    matrix_data_t getMatrix() const;
};

typedef Matrix<float> my_matrix;
typedef QVector<float> my_vector;

template <class T>
Matrix<T>::Matrix(const int row,const int col) :
    matr(QVector< QVector<T> >(row))
{
    this->row = row;
    this->col = col;

    for( int i = 0; i < row; i++ ){
        matr[i] = QVector<T>( col );
    }
}

template <class T>
Matrix<T>::Matrix(const Matrix<T> &copy) :
    row(copy.getRow()),
    col(copy.getCol()),
    matr(matrix_data_t(row))
{
    matrix_data_t copyMatrix = copy.getMatrix();

    for( int i = 0; i < row; i++ ){
        QVector<T> temp =  QVector<T>(copyMatrix.at(i));
        matr[i] = temp;
    }
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &other){

    if( this != &other )
    {
        col = other.getCol();
        row = other.getRow();
        // fit row size
        matr.resize( row );

        for( int rowi = 0; rowi < row; ++rowi )
        {
            my_vector& v = matr[ rowi ];
            v = my_vector( col );
        }
        QPair<int,int> p;
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++)
            {
                p.first = i;
                p.second = j;
                my_vector& v = matr[ i ];
                v[j] = other[p];
            }
        }
    }
    return *this;
}

template <typename T>
Matrix<T>  Matrix<T>::operator*(const Matrix<T>& other) const
{
    if( this->col == other.getRow() )
    {
        Matrix result_matrix( row, other.getCol() );

        QPair< int, int > pnew,
                          pthis,
                          pother;
        T el = 0;
        for( int i = 0; i < row; ++i )
        {
            for( int j = 0; j < result_matrix.getCol(); ++j )
            {
                pthis.first = i;
                pother.second = j;
                for( int k = 0; k < col; ++k)
                {
                    pthis.second = k;
                    pother.first = k;
                    el+= (*this)[pthis] * other[pother];
                }
                pnew.first = i;
                pnew.second = j;
                result_matrix[pnew] = el;
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
    if( other.getCol() != col || other.getRow() != row )
    {
        return *this;
    }

    Matrix<T> newMatrix(row, col);

    for( int i = 0; i < row; i++ )
    {
        for( int j = 0; j < col; j++ )
        {
            newMatrix.set(i, j, get(i, j) - other.get(i, j));
        }
    }

    return newMatrix;
}

template <typename T>
T& Matrix<T>::operator[](QPair<int,int>& p)
{
    QVector<T>& v = matr[p.first];
    return v[p.second];
}

template <typename T>
const T &Matrix<T>::operator [](const QPair<int, int>& p) const
{
    const QVector<T>& v = matr[p.first];
    return v[p.second];
}

template <typename T>
int Matrix<T>::getRow() const
{
    return row;
}

template <typename T>
int Matrix<T>::getCol() const
{
    return col;
}

template <typename T>
void Matrix<T>::set(const int row, const int col, const T val){
    QPair<int,int> p;
    p.first = row;
    p.second = col;
    this->operator [](p) = val;
}

template <typename T>
Matrix<T>  Matrix<T>::operator*(const T val)
{
    Matrix mnew( row, col );
    QPair< int, int > p;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            p.first = i;
            p.second = j;
            mnew.operator [](p) = this->operator [](p)*val;
        }
    }
    return mnew;
}

template <typename T>
T Matrix<T>::get(int row,int col) const
{
    const QVector<T>& v = matr[row];
    return v[col];
}

template <typename T>
QVector<QVector<T> > Matrix<T>::getMatrix() const
{
    return matr;
}

template <typename T>
QString Matrix<T>::toString() const
{
    QString matrixString;
    matrixString.append("{ ");
    for( int i = 0; i < row; i++ )
    {
        matrixString.append("{ ");
        for( int j = 0; j < col; j++ )
        {
            matrixString.append(((j!=0)?",":"") +  QString::number(matr[i][j]));
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

    for( int i = 0; i < row; i++ )
    {
        for( int j = 0; j < col; j++ )
        {
            long int rand_value = rand() % 2001;
            set(i,j, T(rand_value / 1000. - 1));
        }
    }
}

template <typename T>
Matrix<T> Matrix<T>::transpose()
{
    Matrix newMatrix(col, row);

    for( int i = 0; i < row; i++ )
    {
        for( int j = 0; j < col; j++ )
        {
            newMatrix.set(j, i, matr[i][j]);
        }
    }

    return newMatrix;
}

template <typename T>
Matrix<T> Matrix<T>::getVector(int num)
{
    Matrix vector(1, col);

    for( int j = 0; j < col; j++ )
    {
        vector.set(0, j, matr[num][j]);
    }

    return vector;
}

template <typename T>
void Matrix<T>::normalize()
{
    for( int j = 0; j < col; j++ )
    {
        T avg = getAvgForVector(j);

        for( int i = 0; i < row; i++ )
        {
            set(i, j, matr[i][j] / avg);
        }
    }
}

template <typename T>
T Matrix<T>::getAvgForVector(int num)
{
    T sum = 0;

//    T max = -666;
    for( int i = 0; i < row; i++ )
    {
//        if( max < matr[i][num] )
//            max = matr[i][num];
        sum += matr[i][num] * matr[i][num];
    }

    return /*max;*it;*/sqrt( sum );
}

template <typename T>
std::ostream & operator <<(std::ostream &os, const Matrix<T>& obj)
{
    os << obj.row << std::endl;
    os << obj.col << std::endl;
    for( int i = 0; i < obj.row; i++ )
    {
        for( int j = 0; j < obj.col; j++ )
        {
            os << obj.matr[i][j] << " ";
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

    for( int i = 0; i < obj.row; i++ ){
        obj.matr[i] = QVector<T>();
    }

    for( int i = 0; i < obj.row; i++ )
    {
        for( int j = 0; j < obj.col; j++ )
        {
            T v;
            is >> v;
            obj.matr[i].push_back(v);
        }
    }

//    if( /* no valid object of T found in stream */ )
//        is.setstate(std::ios::failbit);
    return is;
}

#endif // MATRIX_H
