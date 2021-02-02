#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QDebug>
#include <QOpenGLWindow>
#include <QJsonDocument>
#include "exportchoice.h"
#include "exportimage.h"
#include "exportvideo.h"
#include "options.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    void on_pushButton_Load_clicked();

    void on_OpenFile_clicked();

    void on_pushButton_Generate_clicked();

    void on_pushPrevious_clicked();

    void on_pushNext_clicked();

    void on_pushButtonExport_clicked();

    void on_verticalSliderColorDepth_valueChanged(int value);

    void on_verticalSliderFrames_valueChanged(int value);

    void on_pushButtonPlay_clicked();

    void exportImages();

    void exportVideoFile();

    void on_pushButton_Options_clicked();

private:
    Ui::MainWindow *ui;
    exportChoice *exportchoice;
    exportImage *exportimage;
    exportVideo *exportvideo;
    Options *options;
    void previousFrame();
    void nextFrame();
    int readCSV(QStringList pathes);
};
#endif // MAINWINDOW_H
