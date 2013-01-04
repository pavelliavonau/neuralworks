#include "neuroapp.h"
#include <QPixmap>

volatile const int NeuroApp::N = 4;
volatile const int NeuroApp::M = 4;
volatile const int NeuroApp::P = 60;
volatile const double NeuroApp::ALPHA = 0.005;


NeuroApp::NeuroApp() :
    mMainWindow( this )
  , mNeuroNet( M * N * 4, P, ALPHA )
  , mMatrix()
{
    mMainWindow.show();
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
    mNeuroNet.train(mMatrix, 10 , 1000);
    mNeuroNet.zipPicture(mMatrix);
}

void NeuroApp::ShowResult()
{

    my_matrix matrix = mNeuroNet.unzipPicture();
    QImage image = mImageProc.GetImageForMatrix(matrix, N, M);
    mMainWindow.ShowResult(image);
}
