#include "neuroapp.h"
#include "Main_Window.h"
#include "logic/Neuro_net.h"
#include "logic/Image_proc.h"

NeuroApp::NeuroApp(int argc, char *argv[]) :
    QApplication(argc, argv)
{
    mMainWindow = new MainWindow();
    mMainWindow->show();

    mNeuroNet = new NeuroNet();
    mImageProc = new ImageProc();
}

NeuroApp::~NeuroApp()
{
    delete mMainWindow;
    delete mNeuroNet;
    delete mImageProc;
}
