#include "Image_proc.h"
#include <fstream>
#include <QDebug>

ImageProc::ImageProc()
{
}

Matrix ImageProc::GetTeachingMatrixFromPicture(QPixmap &pixmap, int n, int m)
{
    std::ofstream stream("input");

    mWidth = pixmap.width();
    mHeight = pixmap.height();

    int cols = n * m * (pixmap.depth() / 8);
    int rows = (pixmap.width() / n) * ( pixmap.height() / m );

    stream << "cols" << cols << std::endl;
    stream << "rows" << rows << std::endl;

    Matrix matrix( rows, cols );

    int row_index = 0;
    int col_index = 0;

    int dx = 1, dy = 1;

    QImage image = pixmap.toImage();

    while ( dy < image.height() )
    {
        for( int y = dy; (y < dy + m) && (dy + m < pixmap.height()); ++y )
        {
            for( int x = dx; (x < dx + n) /*&& (dx+n < pixmap.width())*/; ++x )
            {
                QRgb rgb = image.pixel( x, y );

                matrix.set( row_index, col_index, normalizeColor( qRed( rgb ) ) );
                stream << "row_index" << row_index
                       << " " << "col_index" << col_index << std::endl;
                ++col_index;

                matrix.set( row_index, col_index, normalizeColor( qGreen( rgb ) ) );
                stream << "row_index" << row_index
                       << " " << "col_index" << col_index << std::endl;
                ++col_index;

                matrix.set( row_index, col_index, normalizeColor( qBlue( rgb ) ) );
                stream << "row_index" << row_index
                       << " " << "col_index" << col_index << std::endl;
                ++col_index;

                matrix.set( row_index, col_index, normalizeColor( qAlpha( rgb ) ) );
                stream << "row_index" << row_index
                       << " " << "col_index" << col_index << std::endl;
                ++col_index;                
            }

        }

        col_index = 0;
        ++row_index;
        dx += n;
        if (dx > image.width())
        {            
            dx = 0;
            dy += m;
        }
    }
    stream.close();
    return matrix;
}

QImage ImageProc::GetImageForMatrix(Matrix &mat, int n, int m)
{
    QImage image( mWidth, mHeight, QImage::Format_RGB32 );
    std::ofstream stream("output");
    int row_index = 0;
    int col_index = 0;

    int cols = mat.getCol();
    int rows = mat.getRow();

    int dx = 1, dy = 1;

    while ( row_index < mat.getRow() )          // FIXME
    {
        for( int y = dy; y < dy + m && (dy+m < image.height()); ++y )
        {
            for( int x = dx; (x < dx + n) && (dx+n < image.width()); ++x )
            {
                int red = restoreColor(mat.get(row_index, col_index));
                qDebug() << "row_index" << row_index
                       << " " << "col_index" << col_index;// << std::endl;
                ++col_index;

                int green = restoreColor(mat.get(row_index, col_index));
                qDebug() << "row_index" << row_index
                       << " " << "col_index" << col_index;// << std::endl;
                ++col_index;

                int blue = restoreColor(mat.get(row_index, col_index));
                qDebug() << "row_index" << row_index
                       << " " << "col_index" << col_index;// << std::endl;
                ++col_index;

                int alpha = restoreColor(mat.get(row_index, col_index));
                qDebug() << "row_index" << row_index
                       << " " << "col_index" << col_index;// << std::endl;
                ++col_index;

                image.setPixel(x,y,qRgba(red,green,blue,alpha));
            }

        }
        col_index = 0;
        row_index++;
        dx += n;
        if (dx > image.width())
        {
            dx = 0;
            dy += m;
        }
    }
    return image;
}
