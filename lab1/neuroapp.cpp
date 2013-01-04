#include "neuroapp.h"
#include <QPixmap>
#include <events/logtextevent.h>

volatile const int NeuroApp::COLOR_DEPTH = 3;
volatile const int NeuroApp::N = 2;
volatile const int NeuroApp::M = 2;
volatile const int NeuroApp::P = 8;
volatile const double NeuroApp::ALPHA = 0.003;


NeuroApp::NeuroApp() :
    mMainWindow( this )
  , mNeuroNet( M * N * COLOR_DEPTH, P, ALPHA , this)
  , mMatrix()
{
    mMainWindow.show();
    connect(this,SIGNAL(sendToLog(QString)),&mMainWindow,SLOT(writeToLog(QString)) );
}

NeuroApp::~NeuroApp()
{

}

void NeuroApp::LoadImage()
{
    QPixmap* pix = mMainWindow.loadPixmap();

    mMatrix = my_matrix(mImageProc.GetTeachingMatrixFromPicture(*pix, N, M));
}

void NeuroApp::TeachNeuroNet()
{
    mNeuroNet.train(mMatrix, 50 , 100);
    mNeuroNet.zipPicture(mMatrix);
}

void NeuroApp::ShowResult()
{

    my_matrix matrix = mNeuroNet.unzipPicture();
    QImage image = mImageProc.GetImageForMatrix(matrix, N, M);
    mMainWindow.ShowResult(image);
}

bool NeuroApp::event(QEvent *e)
{
    if (e->type() == QEvent::User + 1)
    {
        LogTextEvent* log_e = dynamic_cast< LogTextEvent* >(e);
        QString t = log_e->getText();
        emit sendToLog(t);
        return true;
    }
    return false;
}
