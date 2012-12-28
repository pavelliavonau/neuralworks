#include "neuroapp.h"
#include <QPixmap>

volatile const int NeuroApp::N = 5;
volatile const int NeuroApp::M = 7;
volatile const int NeuroApp::P = 30;
volatile const double NeuroApp::ALPHA = 0.007;


NeuroApp::NeuroApp() :
    mMainWindow( this )
  , mNeuroNet( M * N, P, ALPHA )
  , mMatrix(0,0)
{
    mMainWindow.show();
}

NeuroApp::~NeuroApp()
{

}

void NeuroApp::LoadImage()
{
    QPixmap* pix = mMainWindow.loadPixmap();

    mMatrix = Matrix(mImageProc.GetTeachingMatrixFromPicture(*pix, N, M));
}

void NeuroApp::TeachNeuroNet()
{
    mNeuroNet.train(mMatrix, 10000 , 3000);
    mNeuroNet.zipPicture(mMatrix);
}

void NeuroApp::ShowResult()
{

    Matrix matrix = mNeuroNet.unzipPicture();
    QImage image = mImageProc.GetImageForMatrix(matrix, N, M);
    mMainWindow.ShowResult(image);
}
