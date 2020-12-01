#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStringList>
#include <QMessageBox>
#include <QVector>
#include <QFileDialog>
#include <algorithm>
QVector <QVector < QVector < double > > > frames;
int currentFrameCount, amountOfFrames;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->labelInfo->setVisible(false);
    ui->pushNext->setIcon(QIcon("/QtProjects/LidarRadarVisualizationQt/nextIcon.png"));
    ui->pushNext->setVisible(false);
    ui->pushPrevious->setIcon(QIcon("/QtProjects/LidarRadarVisualizationQt/previousIcon.png"));
    ui->pushPrevious->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector <double> normalizedNegative1To1(QVector <double> List)
{
    QVector <double> listToReturn;
    double min = *std::min_element(List.constBegin(), List.constEnd());
    double max = *std::max_element(List.constBegin(), List.constEnd());
    double diffMaxMin = max - min;
    for(int i = 0; i<List.size();i++)
    {
        listToReturn.append(((List[i]-min)/(diffMaxMin))*2 - 1);
    }
    return listToReturn;
}

int MainWindow::readCSV(QStringList pathes)
{

    QVector<double> xList;
    QVector<double> yList;
    QVector<double> zList;
    QVector<QVector <double>> coordinates;
    frames.clear();
    ui->G->setEnabled(true);
    ui->G->setValue(5);
    for(int i= 0;i<pathes.size();i++)
    {
        QString nameFile = pathes[i];
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
        QByteArray line = file.readLine();
        bool ok;
        while (!file.atEnd())
        {
            line = file.readLine();
            xList.append(line.split(',')[0].toDouble(&ok));
            yList.append(line.split(',')[1].toDouble(&ok));
            zList.append(line.split(',')[2].toDouble(&ok));
        }
        coordinates.append(normalizedNegative1To1(xList));
        coordinates.append(normalizedNegative1To1(yList));
        coordinates.append(normalizedNegative1To1(zList));
        frames.append(coordinates);
        coordinates.clear();
        ui->G->setValue(((i+1)*100)/(pathes.size()));
        qApp->processEvents();
    }
    currentFrameCount = 1;
    amountOfFrames = frames.size();
    return 0;

}

void MainWindow::on_pushButton_Load_clicked()
{
    QStringList pathes = ui->linePath->text().split(',');
    if(readCSV(pathes))
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
    QStringList filenames = QFileDialog::getOpenFileNames(
                this,
                tr("Open File"),
                "C://",
                "Text csv (*.csv)"
                );
    ui->linePath->clear();
    ui->linePath->insert(filenames[0]);
    for(int i =1;i<filenames.size();i++)
    {
        ui->linePath->insert(",");
        ui->linePath->insert(filenames[i]);
    }
}

void MainWindow::on_pushButton_Generate_clicked()
{
    ui->OpenGLWidget->takeVectors(frames[currentFrameCount-1][0],frames[currentFrameCount-1][1],frames[currentFrameCount-1][2]);
    if(amountOfFrames>1)
    {
        ui->pushNext->setVisible(true);
        ui->pushPrevious->setVisible(true);
        ui->pushPrevious->setEnabled(false);
    }
    else{
        ui->pushNext->setVisible(false);
        ui->pushPrevious->setVisible(false);
    }
    ui->labelFrame->setText(QString::number(currentFrameCount)+"/"+QString::number(amountOfFrames));
}


void MainWindow::on_pushPrevious_clicked()
{
    currentFrameCount-=1;
    ui->OpenGLWidget->takeVectors(frames[currentFrameCount-1][0],frames[currentFrameCount-1][1],frames[currentFrameCount-1][2]);
    if(currentFrameCount==1)
    {
        ui->pushPrevious->setEnabled(false);
    }
    ui->pushNext->setEnabled(true);
    ui->labelFrame->setText(QString::number(currentFrameCount)+"/"+QString::number(amountOfFrames));

}

void MainWindow::on_pushNext_clicked()
{
    currentFrameCount+=1;
    ui->OpenGLWidget->takeVectors(frames[currentFrameCount-1][0],frames[currentFrameCount-1][1],frames[currentFrameCount-1][2]);
    if(currentFrameCount==amountOfFrames)
    {
        ui->pushNext->setEnabled(false);
    }
    ui->pushPrevious->setEnabled(true);
    ui->labelFrame->setText(QString::number(currentFrameCount)+"/"+QString::number(amountOfFrames));

}
