#ifndef NEURO_NET_H
#define NEURO_NET_H

#include <QtCore/qglobal.h>
#include "matrix.h"

//class Matrix;

class NeuroNet
{
public:
    NeuroNet(int first_layer, int second_layer, double alpha = 0);
    bool train(Matrix &trainData, int maxIteration, int maxError);
    void zipPicture(Matrix& matrix);
    Matrix unzipPicture();

private:
    void accomulateError(double &error, Matrix &vector);
    void trainLayers(Matrix &delta, Matrix &input, Matrix& out);
    qreal alpha(Matrix &vector);

    Matrix  mTrainData;
    int     mNeuronsOnLastLayer;
    Matrix  mFirstLayer;
    Matrix  mSecondLayer;
    qreal   mAlpha;
};

#endif // NEURO_NET_H
