#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStringList>
#include <QMessageBox>
#include <QVector>
#include <QFileDialog>

QVector<double> xList;
QVector<double> yList;
QVector<double> zList;


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
    xList.clear();
    yList.clear();
    zList.clear();
    int count = 0;
    QByteArray line = file.readLine();
    bool ok;
    while (!file.atEnd()) {
        line = file.readLine();
        count++;
        xList.append(line.split(',')[0].toDouble(&ok));
        yList.append(line.split(',')[1].toDouble(&ok));
        zList.append(line.split(',')[2].toDouble(&ok));
    }

    qDebug() << xList[0];
    return 0;

}


void MainWindow::on_pushButton_Load_clicked()
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
        ui->pushButton_Generate->setEnabled(true);
    }
}



void MainWindow::on_OpenFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "Text csv (*.csv)"
                );
    ui->linePath->insert(filename);
}

void MainWindow::on_pushButton_Generate_clicked()
{
    qDebug() << xList[0];
    ui->OpenGLWidget->takeVectors(xList,yList,zList);
    ui->G->setEnabled(true);
    ui->G->setValue(100); //tymczasowo
}

