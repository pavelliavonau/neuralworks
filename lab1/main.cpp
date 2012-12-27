#include <QApplication>
#include "neuroapp.h"
#include "Main_Window.h"

int main(int argc, char *argv[])
{
    QApplication a( argc, argv );
    NeuroApp neuro;
    return a.exec();
}
