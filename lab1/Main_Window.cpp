#include "Main_Window.h"
#include "ui_Main_Window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::on_actionLoad_image_triggered()
{

}

void MainWindow::on_actionTeach_net_triggered()
{

}

void MainWindow::on_actionDraw_result_triggered()
{

}
