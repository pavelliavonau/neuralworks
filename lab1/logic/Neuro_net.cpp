#include "Neuro_net.h"
#include "logic/matrix.h"

NeuroNet::NeuroNet(int neuronsOnFirstLayer, int neuronsOnSecondLayer, double alpha):
    mAlpha(alpha)
{
    mFirstLayer = new Matrix(neuronsOnFirstLayer, neuronsOnSecondLayer);
    mFirstLayer->randomInitialize();

    mSecondLayer = new Matrix(mFirstLayer->transpose());
}

bool NeuroNet::train(Matrix &trainData, int maxIteration, int maxError)
{
    double error = 0, it = 0;

    while( error > maxError && it < maxIteration )
    {
        error = 0;

        for( int i = 0; i < trainData.getRow(); i++ )
        {
            Matrix inData = trainData.getVector(i),

                   outData = inData * (*mFirstLayer),
                   restoredData = outData * (*mSecondLayer),
                   delta = restoredData - trainData.getVector(i);

            accomulateError(error, delta);
            trainLayers(delta, inData, outData);
        }

        it++;
    }

    return true;
}

void NeuroNet::accomulateError(double &error, Matrix &vector)
{
    for( int j = 0; j < vector.getCol(); j++ )
    {
        error += vector.get(1, j) * vector.get(1, j);
    }
}

void NeuroNet::trainLayers(Matrix &delta, Matrix &input, Matrix& out)
{
    Matrix *oldFirst = mFirstLayer, *oldSecond = mSecondLayer;

    mFirstLayer = new Matrix(*mFirstLayer - input.transpose()* alpha(input) * delta * mSecondLayer->transpose());
    mSecondLayer = new Matrix(*mSecondLayer - out.transpose()* alpha(out) * delta);

    mFirstLayer->normalize();
    mSecondLayer->normalize();

    delete oldFirst;
    delete oldSecond;
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
        result += vector.get(1, j) * vector.get(1, j);
    }

    return 1/result;
}
