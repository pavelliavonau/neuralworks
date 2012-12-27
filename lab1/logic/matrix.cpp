#include "matrix.h"

Matrix::Matrix(const int row,const int col) :
    matr(QVector<QVector<qreal>*>(row,0))
{
    this->row = row;
    this->col = col;

    for( int i = 0; i < row; i++ ){
        matr[i] = new QVector<qreal>( col, 0 );
    }
}

Matrix::Matrix(const Matrix &copy) :
    row(copy.getRow()),
    col(copy.getCol()),
    matr(QVector<QVector<qreal>*>(row,0))
{
    QVector<QVector<qreal>*> copyMatrix = copy.getMatrix();

    for( int i = 0; i < row; i++ ){
        QVector<qreal>* temp =  new QVector<qreal>(*copyMatrix.at(i));
        matr[i] = temp;
    }
}

Matrix::~Matrix()
{
    for( int i = 0; i < row; i++ ){
        QVector<qreal>* pVector = matr[i];
        delete pVector;
    }
}

Matrix& Matrix::operator=(const Matrix &other){

    if(this != &other){
        col = other.getCol();
        row = other.getRow();
        matr.resize(row);
        QVector<qreal> *v;
        for(int i = 0;i<col;i++){
            v = matr.operator [](i);
            v->resize(col);
        }
        QPair<int,int> p;
        for(int i = 0;i<row;i++){
            for(int j = 0;j<col;j++)
            {
                p.first = i;
                p.second = j;
                v = matr.operator [](i);
                v->operator [](j) = other.operator [](p);
            }
        }
    }
    return *this;
}

Matrix  Matrix::operator*(const Matrix& other) const
{
    if(col==other.getRow()){
        Matrix mnew(row,other.getCol());
        QPair<int,int> pnew,pthis,pother;
        qreal el = 0;
        for( int i = 0; i<row; i++ ){
            for( int j = 0; j < mnew.getCol(); j++ ){
                pthis.first = i;
                pother.second = j;
                for(int k = 0;k < col;k++){
                    pthis.second = k;
                    pother.first = k;
                    el+= this->operator [](pthis)*other.operator [](pother);
                }
                pnew.first = i;
                pnew.second = j;
                mnew.operator [](pnew) = el;
                el = 0;
            }
        }
        return mnew;
    }
    return *this;
}

qreal& Matrix::operator[](QPair<int,int> p) const
{
    QVector<qreal> *v = matr.operator [](p.first);
    return v->operator [](p.second);
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

Matrix  Matrix::operator*(const qreal val){
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

qreal Matrix::get(int row,int col) const{
    QVector<qreal> *v = matr.operator [](row);
    return v->operator [](col);
}

QVector<QVector<qreal> *> Matrix::getMatrix() const
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
            matrixString.append(((j!=0)?",":"") +  QString::number(matr[i]->at(j)));
        }
        matrixString.append("}\n");
    }
    matrixString.append("}");
    return matrixString;
}
