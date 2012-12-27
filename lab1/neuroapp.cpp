#include "neuroapp.h"
#include <QPixmap>

volatile const int NeuroApp::N = 5;
volatile const int NeuroApp::M = 7;
volatile const int NeuroApp::P = 30;


NeuroApp::NeuroApp() :
    mMainWindow( this )
  //, mNeuroNet( this )
  //, mImageProc( )
{
//    mMainWindow = new MainWindow(this);
    mMainWindow.show();

}

NeuroApp::~NeuroApp()
{

}

void NeuroApp::LoadImage()
{
    QPixmap* pix = mMainWindow.loadPixmap();

    Matrix matrix = mImageProc.GetTeachingMatrixFromPicture(*pix, N, M);

}
