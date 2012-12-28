#ifndef MATRIX_H
#define MATRIX_H
#include <QVector>
#include <QPair>
#include <iostream>

typedef QVector< QVector<qreal> > matrix_data_t;

class Matrix
{
    int row;
    int col;

    matrix_data_t matr;
    qreal getAvgForVector( int num );

public:
    Matrix( const int row = 0,const int col = 0 );
    Matrix( Matrix const & copy );
    virtual ~Matrix();
    Matrix& operator=( const Matrix& );
    Matrix operator*( const Matrix& ) const;
    Matrix operator-( const Matrix& ) const;
    Matrix operator*( const qreal );
    void set( const int, const int, const qreal );
    qreal get(int,int) const;
    int getCol() const;
    int getRow() const;
    QString toString() const;
    void randomInitialize();
    Matrix transpose();
    Matrix getVector( int num );
    void normalize();

    friend std::ostream& operator<<( std::ostream& os, const Matrix& obj );
    friend std::istream& operator>>( std::istream& is, Matrix& obj );

    qreal& operator[]( QPair< int, int >& );
    const qreal& operator[]( const QPair< int, int >& ) const;
    matrix_data_t getMatrix() const;
};

#endif // MATRIX_H
