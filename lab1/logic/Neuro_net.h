#ifndef NEURO_NET_H
#define NEURO_NET_H

#include <QtCore/qglobal.h>
#include "matrix.h"

class NeuroNet
{        
public:
    NeuroNet(int first_layer, int second_layer, double alpha, QObject* receiver );
    bool train(my_matrix &trainData, int maxIteration, int maxError);
    void zipPicture(my_matrix& matrix);
    my_matrix unzipPicture();

private:
    void accomulateError(double &error, my_matrix &vector);
    void trainLayers(my_matrix &delta, my_matrix &input, my_matrix& out);
    qreal alpha(my_matrix &vector);
    void sendLogText(QString);

    my_matrix  mTrainData;
    int     mNeuronsOnLastLayer;
    my_matrix  mFirstLayer;
    my_matrix  mSecondLayer;
    qreal   mAlpha;
    QObject* m_receiver;
};

#endif // NEURO_NET_H
