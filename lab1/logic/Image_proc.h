#ifndef IMAGE_PROC_H
#define IMAGE_PROC_H

#include <QPixmap>
#include "logic/matrix.h"

class NeuroApp;
class Matrix;

class ImageProc
{
public:
    ImageProc(/*NeuroApp* app*/);

    Matrix GetTeachingMatrixFromPicture(QPixmap& pixmap, int n, int m);

private:
    //NeuroApp* mNeuroApp;
};

#endif // IMAGE_PROC_H
