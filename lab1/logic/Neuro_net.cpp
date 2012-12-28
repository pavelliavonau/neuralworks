#include "Neuro_net.h"
#include "logic/matrix.h"
#include <fstream>
#include <QDebug>

NeuroNet::NeuroNet(int neuronsOnFirstLayer, int neuronsOnSecondLayer, double alpha):
    mAlpha(alpha)
  , mFirstLayer(neuronsOnFirstLayer, neuronsOnSecondLayer)
{  
    mFirstLayer.randomInitialize();

    int cols = mFirstLayer.getCol();
    int rows = mFirstLayer.getRow();

    mSecondLayer = Matrix(mFirstLayer.transpose());
    cols = mSecondLayer.getCol();
    rows = mSecondLayer.getRow();
}

bool NeuroNet::train(Matrix &trainData, int maxIteration, int maxError)
{
    double error = maxError + 1, it = 0;

    while( error > maxError && it < maxIteration )
    {
        error = 0;

        for( int i = 0; i < trainData.getRow(); i++ )
        {
            Matrix inData = trainData.getVector(i),

                   outData = inData * mFirstLayer,
                   restoredData = outData * mSecondLayer,
                   delta = restoredData - trainData.getVector(i);

            accomulateError(error, delta);
            trainLayers(delta, inData, outData);

        }
        qDebug() << it;
        it++;
    }

    return true;
}

void NeuroNet::zipPicture(Matrix &matrix)
{
    Matrix temp = mFirstLayer * matrix;         //FIXME!!

    std::ofstream file("temp.out");

    file << temp;

    int cols = temp.getCol();
    int rows = temp.getRow();

    file.close();

}

Matrix NeuroNet::unzipPicture()
{
    std::ifstream file("temp.out");
    Matrix temp(0,0);
    file >> temp;

    int cols = temp.getCol();
    int rows = temp.getRow();

    cols = mSecondLayer.getCol();
    rows = mSecondLayer.getRow();

    file.close();
    return temp * mSecondLayer;
}

void NeuroNet::accomulateError(double &error, Matrix &vector)
{
    for( int j = 0; j < vector.getCol(); j++ )
    {
        error += vector.get(0, j) * vector.get(0, j);
    }
}

void NeuroNet::trainLayers(Matrix &delta, Matrix &input, Matrix& out)
{
    mFirstLayer = Matrix(mFirstLayer - input.transpose()* alpha(input) * delta * mSecondLayer.transpose());
    mSecondLayer = Matrix(mSecondLayer - out.transpose()* alpha(out) * delta);

    int cols = mSecondLayer.getCol();
    int rows = mSecondLayer.getRow();

    mFirstLayer.normalize();
    mSecondLayer.normalize();
}

qreal NeuroNet::alpha(Matrix &vector)
{
    if(mAlpha != 0)
    {
        return mAlpha;
    }

    qreal result = 0;

    for( int j = 0; j < vector.getCol(); j++ )
    {
        result += vector.get(0, j) * vector.get(0, j);
    }

    return 1/result;
}
