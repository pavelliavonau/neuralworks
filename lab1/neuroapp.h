#ifndef NEUROAPP_H
#define NEUROAPP_H

#include "Main_Window.h"
#include "logic/Neuro_net.h"
#include "logic/Image_proc.h"

class MainWindow;
class NeuroNet;
class ImageProc;

class NeuroApp : public QObject
{
    Q_OBJECT
public:
    explicit NeuroApp();
    virtual ~NeuroApp();
    
    static volatile const int COLOR_DEPTH;
    static volatile const int N;
    static volatile const int M;
    static volatile const int P;
    static volatile const double ALPHA;

    void LoadImage();    
    void TeachNeuroNet();
    void ShowResult();

protected:
    bool event(QEvent *);

private:
    MainWindow      mMainWindow;
    NeuroNet        mNeuroNet;
    ImageProc       mImageProc;
    my_matrix       mMatrix;
    
public slots:

signals:
    void sendToLog(QString);
    
};

#endif // NEUROAPP_H
