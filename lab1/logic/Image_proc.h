#ifndef IMAGE_PROC_H
#define IMAGE_PROC_H

#include <QPixmap>
#include "logic/matrix.h"

class NeuroApp;

class ImageProc
{
public:
    ImageProc();

    my_matrix GetTeachingMatrixFromPicture(QPixmap& pixmap, int n, int m);
    QImage GetImageForMatrix(my_matrix& mat, int n, int m);

private:

    inline double normalizeColor(int value)
    { return 2 * static_cast<double>(value) / 256 - 1; }

    inline int restoreColor(qreal value)
    { return (256 * (value + 1))/2; }


    int mWidth;
    int mHeight;
    //NeuroApp* mNeuroApp;
};

#endif // IMAGE_PROC_H
