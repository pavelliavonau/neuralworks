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

    mSecondLayer = my_matrix(mFirstLayer.transpose());
    cols = mSecondLayer.getCol();
    rows = mSecondLayer.getRow();
}

bool NeuroNet::train(my_matrix &trainData, int maxIteration, int maxError)
{
    double error = maxError + 1, it = 0;

    while( error > maxError && it < maxIteration )
    {
        error = 0;

        for( int i = 0; i < trainData.getRow(); i++ )
        {
            my_matrix inData = trainData.getVector(i),

                   outData = inData * mFirstLayer,
                   restoredData = outData * mSecondLayer,
                   delta = restoredData - trainData.getVector(i);

            accomulateError(error, delta);
            trainLayers(delta, inData, outData);
            //qDebug() << "it= " << it << " error = " << error;
        }
        qDebug() << "it= " << it << " error = " << error;
        it++;
    }

    return true;
}

void NeuroNet::zipPicture(my_matrix &matrix)
{
    my_matrix temp = matrix * mFirstLayer;

    std::ofstream file("temp.out");

    file << temp;

    file.close();

}

my_matrix NeuroNet::unzipPicture()
{
    std::ifstream file("temp.out");
    my_matrix temp(0,0);
    file >> temp;

    int cols = temp.getCol();
    int rows = temp.getRow();

    cols = mSecondLayer.getCol();
    rows = mSecondLayer.getRow();

    file.close();
    return temp * mSecondLayer;
}

void NeuroNet::accomulateError(double &error, my_matrix &vector)
{
    for( int j = 0; j < vector.getCol(); j++ )
    {
        error += vector.get(0, j) * vector.get(0, j);
    }
}

void NeuroNet::trainLayers( my_matrix &delta, my_matrix &input, my_matrix &out )
{
    mFirstLayer = my_matrix( mFirstLayer - input.transpose() * alpha(input) * delta * mSecondLayer.transpose());
    mSecondLayer = my_matrix( mSecondLayer - out.transpose()* alpha(out) * delta);


    mFirstLayer.normalize();
    mSecondLayer.normalize();
}

qreal NeuroNet::alpha(my_matrix &vector)
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
