#include "Neuro_net.h"
#include "logic/matrix.h"
#include <fstream>
#include <QDebug>
#include "events/logtextevent.h"
#include <QApplication>

NeuroNet::NeuroNet(int neuronsOnFirstLayer, int neuronsOnSecondLayer, double alpha, QObject* receiver):
    mFirstLayer(neuronsOnFirstLayer, neuronsOnSecondLayer)
  , mAlpha(alpha)
  , m_receiver(receiver)
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
    double error = maxError + 1;
    int it = 0;

    int train_data_row_count = trainData.getRow();

    while( error > maxError && it < maxIteration )
    {
        error = 0;

        for( int i = 0; i < train_data_row_count; i++ )
        {
            my_matrix inData = trainData.getVector(i);

            my_matrix outData = inData * mFirstLayer;
            my_matrix restoredData = outData * mSecondLayer;
            my_matrix delta = restoredData - trainData.getVector(i);

            accomulateError(error, delta);
            trainLayers(delta, inData, outData);            
        }
        sendLogText("it= " + QString::number(it) + " error = " + QString::number(error) + "\n");
        qDebug() << "it= " << it << " error = " << error;
        it++;
    }
    qDebug() << "finished!";
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
        error += std::pow(vector.get(0, j), 2);
    }
}

void NeuroNet::trainLayers( my_matrix &delta, my_matrix &input, my_matrix &out )
{
    mFirstLayer -= input.transpose() * alpha(input) * delta * mSecondLayer.transpose();
    mSecondLayer -= out.transpose() * alpha(out) * delta;


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

void NeuroNet::sendLogText(QString text)
{
    LogTextEvent log_event;
    log_event.setText(text);
    //QMouseEvent event(QEvent::MouseButtonPress, pos, 0, 0, 0);
    QApplication::sendEvent(m_receiver, &log_event);
}
