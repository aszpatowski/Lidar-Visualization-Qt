#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QDebug>
#include <QOpenGLWindow>
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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
