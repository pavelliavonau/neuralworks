#include "Image_proc.h"
//#include <fstream>
#include <QDebug>

ImageProc::ImageProc()
{
}

my_matrix ImageProc::GetTeachingMatrixFromPicture(QPixmap &pixmap, int n, int m)
{

    mWidth = pixmap.width();
    mHeight = pixmap.height();

    int cols = n * m * 3;
    int rows = (pixmap.width() / n) * ( pixmap.height() / m );

    my_matrix matrix( rows, cols );

    int row_index = 0;
    int col_index = 0;

    int dx = 0, dy = 0;

    QImage image = pixmap.toImage();

    while ( dy < mHeight )
    {
        for( int y = dy; (y < dy + m) /*&& (y < mHeight)*//*&& (dy + m < pixmap.height())*/; ++y )
        {
            for( int x = dx; (x < dx + n) /*&& (x < mWidth)*/; ++x )
            {
                QRgb rgb = image.pixel( x, y );

                matrix.set( row_index, col_index, normalizeColor( qRed( rgb ) ) );
//                qDebug() << "row_index" << row_index
//                       << " " << "col_index" << col_index;// << std::endl;
                ++col_index;

                matrix.set( row_index, col_index, normalizeColor( qGreen( rgb ) ) );
//                qDebug() << "row_index" << row_index
//                       << " " << "col_index" << col_index;// << std::endl;
                ++col_index;

                matrix.set( row_index, col_index, normalizeColor( qBlue( rgb ) ) );
//                qDebug() << "row_index" << row_index
//                       << " " << "col_index" << col_index;// << std::endl;
                ++col_index;

//                matrix.set( row_index, col_index, normalizeColor( qAlpha( rgb ) ) );
////                qDebug() << "row_index" << row_index
////                       << " " << "col_index" << col_index;// << std::endl;
//                ++col_index;
                //qDebug() << "x = " << dx + x;
            }
        }

        col_index = 0;
        ++row_index;        
        dx += n;        

        if (dx >= image.width())
        {
            dx = 0;
            dy += m;
        }
//        qDebug() << row_index << "dx = " << dx;
    }
//    stream.close();
    return matrix;
}

QImage ImageProc::GetImageForMatrix(my_matrix &mat, int n, int m)
{
    QImage image( mWidth, mHeight, QImage::Format_RGB32 );
//    std::ofstream stream("output");
    int row_index = 0;
    int col_index = 0;

    int dx = 0, dy = 0;

    while ( row_index < mat.getRow() )
    {
        for( int y = dy; y < dy + m; ++y )
        {
            for( int x = dx; (x < dx + n) && (dx+n <= image.width()); ++x )
            {
                int red = restoreColor(mat.get(row_index, col_index));
                ++col_index;

                int green = restoreColor(mat.get(row_index, col_index));
                ++col_index;

                int blue = restoreColor(mat.get(row_index, col_index));
                ++col_index;

                int alpha = restoreColor(/*mat.get(row_index, col_index)*/0);
//                qDebug() << "row_index" << row_index
//                       << " " << "col_index" << col_index;// << std::endl;
                //++col_index;

                image.setPixel( x, y, qRgba( red, green, blue, alpha ) );
            }
        }
        col_index = 0;
        row_index++;
        dx += n;
        if (dx >= image.width())
        {
            dx = 0;
            dy += m;
        }
    }
    return image;
}
