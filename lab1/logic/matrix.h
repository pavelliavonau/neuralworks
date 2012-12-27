#ifndef MATRIX_H
#define MATRIX_H
#include <QVector>
#include <QPair>

class Matrix
{
    int row;
    int col;
    QVector<QVector<qreal>*> matr;
    QVector<QVector<qreal>*> getMatrix() const;

public:
    Matrix(const int row,const int col);
    Matrix(Matrix const & copy);
    virtual ~Matrix();
    Matrix& operator=(const Matrix&);
    Matrix operator*(const Matrix&) const;
    Matrix operator*(const qreal);
    void set( const int, const int, const qreal );
    qreal get(int,int) const;
    int getCol() const;
    int getRow() const;
    QString toString() const;

    qreal& operator[](QPair<int,int>) const;

};

#endif // MATRIX_H
