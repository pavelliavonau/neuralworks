#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class NeuroApp;
class QPixmap;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(NeuroApp *app);
    ~MainWindow();
    
    QPixmap* loadPixmap();
    void ShowResult(QImage);

private slots:
    void on_actionQuit_triggered();

    void on_actionLoad_image_triggered();

    void on_actionTeach_net_triggered();

    void on_actionDraw_result_triggered();

private:
    Ui::MainWindow *ui;
    QPixmap         mLoadedPicture;
    NeuroApp        *mNeuroApp;

};

#endif // MAIN_WINDOW_H
