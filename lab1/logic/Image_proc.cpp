#include "Image_proc.h"

ImageProc::ImageProc()
    //: mNeuroApp(app)
{
}

Matrix ImageProc::GetTeachingMatrixFromPicture(QPixmap &pixmap, int n, int m)
{

    int rows = n * m * (pixmap.depth() / 8);
    int cols = (pixmap.width() / n) * ( pixmap.height() / m );
    Matrix matrix( rows, cols );




    return matrix;
}
