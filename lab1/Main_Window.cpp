#include "Main_Window.h"
#include "ui_Main_Window.h"
#include <QFileDialog>
#include "logic/Neuro_net.h"
#include "neuroapp.h"

MainWindow::MainWindow(NeuroApp *app):
    ui(new Ui::MainWindow)
  , mNeuroApp(app)
{
    ui->setupUi(this);    
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPixmap *MainWindow::loadPixmap()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    QString(),
                                                    tr("Images (*.png *.xpm *.jpg *.bmp)")
                                                   );
    mLoadedPicture.load(fileName);
    ui->LoadedImage->setPixmap(mLoadedPicture);

    return &mLoadedPicture;
}

void MainWindow::ShowResult(QImage image)
{

    ui->CalculatedImage->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::on_actionLoad_image_triggered()
{
    mNeuroApp->LoadImage();
}

void MainWindow::on_actionTeach_net_triggered()
{
    mNeuroApp->TeachNeuroNet();
}

void MainWindow::on_actionDraw_result_triggered()
{
    mNeuroApp->ShowResult();
}

void MainWindow::writeToLog(QString text)
{
    ui->logWidget->appendPlainText(text);
    repaint();
}
