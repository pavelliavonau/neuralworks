#include "Image_proc.h"

ImageProc::ImageProc()
{
}

Matrix ImageProc::GetTeachingMatrixFromPicture(QPixmap &pixmap, int n, int m)
{

    int cols = n * m * (pixmap.depth() / 8);
    int rows = (pixmap.width() / n) * ( pixmap.height() / m );
    Matrix matrix( rows, cols );

    int row_index = 0;
    int col_index = 0;

    int dx = 1, dy = 1;

    QImage image = pixmap.toImage();

    while ( dy < image.height() )
    {
        for( int y = dy; y < dy + m; ++y )
        {
            for( int x = dx; x < dx + n; ++x )
            {
                QRgb rgb = image.pixel( x, y );

                matrix.set( row_index, col_index, qRed(rgb));
                ++col_index;
                matrix.set( row_index, col_index, qGreen(rgb));
                ++col_index;
                matrix.set( row_index, col_index, qBlue(rgb));
                ++col_index;
            }

        }
        col_index = 0;
        dx += n;
        if (dx > image.width())
        {
            ++row_index;
            dx = 0;
            dy += m;
        }
    }

    return matrix;
}
