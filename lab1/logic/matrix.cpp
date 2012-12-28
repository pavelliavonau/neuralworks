#include "matrix.h"
#include "stdlib.h"
#include <QTime>

Matrix::Matrix(const int row,const int col) :
    matr(matrix_data_t(row))
{
    this->row = row;
    this->col = col;

    for( int i = 0; i < row; i++ ){
        matr[i] = QVector<qreal>( col );
    }
}

Matrix::Matrix(const Matrix &copy) :
    row(copy.getRow()),
    col(copy.getCol()),
    matr(matrix_data_t(row))
{
    matrix_data_t copyMatrix = copy.getMatrix();

    for( int i = 0; i < row; i++ ){
        QVector<qreal> temp =  QVector<qreal>(copyMatrix.at(i));
        matr[i] = temp;
    }
}

Matrix::~Matrix()
{
//    for( int i = 0; i < row; i++ ){
//        QVector<qreal> pVector = matr[i];
//        delete pVector;
//    }
}

Matrix& Matrix::operator=(const Matrix &other){

    if( this != &other )
    {
        col = other.getCol();
        row = other.getRow();
        // fit row size
        matr.resize( row );

        for( int rowi = 0; rowi < row; ++rowi )
        {
            QVector<qreal>& v = matr[ rowi ];
            //if( col < v.size() )                    // FIXME! v may be undef
//            {
               v = QVector<qreal>( col );
//            }
        }
        QPair<int,int> p;
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++)
            {
                p.first = i;
                p.second = j;
                QVector<qreal>& v = matr[ i ];
                v[j] = other[p];
            }
        }
    }
    return *this;
}

Matrix  Matrix::operator*(const Matrix& other) const
{
    if( col == other.getRow() )
    {
        Matrix result_matrix( row, other.getCol() );

        QPair< int, int > pnew,
                          pthis,
                          pother;
        qreal el = 0;
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
    return *this;
}

Matrix Matrix::operator-(const Matrix &other) const
{
    if( other.getCol() != col || other.getRow() != row )
    {
        return *this;
    }

    Matrix newMatrix(row, col);

    for( int i = 0; i < row; i++ )
    {
        for( int j = 0; j < col; j++ )
        {
            newMatrix.set(i, j, get(i, j) - other.get(i, j));
        }
    }

    return newMatrix;
}

qreal& Matrix::operator[](QPair<int,int>& p)
{
    QVector<qreal>& v = matr[p.first];
    return v[p.second];
}

const qreal &Matrix::operator [](const QPair<int, int>& p) const
{
    const QVector<qreal>& v = matr[p.first];
    return v[p.second];
}

int Matrix::getRow() const
{
    return row;
}

int Matrix::getCol() const
{
    return col;
}

void Matrix::set(const int row, const int col, const qreal val){
    QPair<int,int> p;
    p.first = row;
    p.second = col;
    this->operator [](p) = val;
}

Matrix  Matrix::operator*(const qreal val)
{
    Matrix mnew(row,col);
    QPair<int,int> p;
    for(int i = 0;i<row;i++){
        for(int j = 0;j<col;j++){
            p.first = i;
            p.second = j;
            mnew.operator [](p) = this->operator [](p)*val;
        }
    }
    return mnew;
}

qreal Matrix::get(int row,int col) const
{
    const QVector<qreal>& v = matr[row];
    return v[col];
}

matrix_data_t Matrix::getMatrix() const
{
    return matr;
}

QString Matrix::toString() const
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

void Matrix::randomInitialize()
{
    qsrand(QTime::currentTime().msec());

    for( int i = 0; i < row; i++ )
    {
        for( int j = 0; j < col; j++ )
        {
            long int rand_value = rand() % 2001;
            set(i,j, qreal(rand_value / 1000. - 1));
        }
    }
}

Matrix Matrix::transpose()
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

Matrix Matrix::getVector(int num)
{
    Matrix vector(1, col);

    for( int j = 0; j < col; j++ )
    {
        vector.set(0, j, matr[num][j]);
    }

    return vector;
}

void Matrix::normalize()
{
    for( int j = 0; j < col; j++ )
    {
        qreal avg = getAvgForVector(j);

        for( int i = 0; i < row; i++ )
        {
            set(i, j, matr[i][j]/avg);
        }
    }
}

qreal Matrix::getAvgForVector(int num)
{
    qreal sum = 0;

    for( int i = 0; i < row; i++ )
    {
        sum += matr[i][num];
    }

    return sum/row;
}

std::ostream & operator <<(std::ostream &os, const Matrix& obj)
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

std::istream & operator >>(std::istream &is, Matrix& obj)
{
//    for( int i = 0; i < obj.getRow(); i++ ){
//        QVector<qreal>* pVector = obj.matr[i];
//        delete pVector;
//    }

    int row, col;

    is >> row;
    is >> col;

    obj = Matrix( row, col );

    for( int i = 0; i < obj.row; i++ ){
        obj.matr[i] = QVector<qreal>( obj.col, 0 );
    }

    for( int i = 0; i < obj.row; i++ )
    {
        for( int j = 0; j < obj.col; j++ )
        {
            qreal v;
            is >> v;
            obj.matr[i].push_back(v);
        }
    }

//    if( /* no valid object of T found in stream */ )
//        is.setstate(std::ios::failbit);
    return is;
}

