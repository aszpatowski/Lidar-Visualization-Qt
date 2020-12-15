#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QDebug>
#include <QOpenGLWindow>
#include "exportchoice.h"
#include "exportimage.h"
#include "exportvideo.h"
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

private:
    Ui::MainWindow *ui;
    exportChoice *exportchoice;
    exportImage *exportimage;
    exportVideo *exportvideo;
    int readCSV(QStringList pathes);
};
#endif // MAINWINDOW_H
