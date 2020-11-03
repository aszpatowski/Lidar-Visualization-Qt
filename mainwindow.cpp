#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStringList>
#include <QMessageBox>
#include <QVector>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->labelInfo->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int readCSV(QString nameFile)
{
    QByteArray name = nameFile.toLocal8Bit();
    const char *c_nameFile = name.data();
    QFile file(c_nameFile);
    if (!file.open(QIODevice::ReadOnly))
    {
            qDebug() << file.errorString();
            return 1;
    }
    QStringList xList;
    QStringList yList;
    QStringList zList;
    int count = 0;
    QByteArray line = file.readLine();
    while (!file.atEnd()) {
        line = file.readLine();
        count++;
        xList.append(line.split(',')[0]);
        yList.append(line.split(',')[1]);
        zList.append(line.split(',')[2]);
    }

    qDebug() << count;
    return 0;

}


void MainWindow::on_pushButton_Generate_clicked()
{
    QString text = ui->linePath->text();
    if(readCSV(text))
    {
        ui->labelInfo->setText("Porażka");
        ui->labelInfo->setVisible(true);
    }
    else
    {
        ui->labelInfo->setText("Sukces");
        ui->labelInfo->setVisible(true);
    }
}


