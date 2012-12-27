#ifndef NEUROAPP_H
#define NEUROAPP_H

#include <QApplication>

class MainWindow;
class NeuroNet;
class ImageProc;

class NeuroApp : public QApplication
{
    Q_OBJECT
public:
    explicit NeuroApp(int argc, char *argv[]);
    virtual ~NeuroApp();
    
private:
    MainWindow*     mMainWindow;
    NeuroNet*       mNeuroNet;
    ImageProc*      mImageProc;

signals:
    
public slots:
    
};

#endif // NEUROAPP_H
