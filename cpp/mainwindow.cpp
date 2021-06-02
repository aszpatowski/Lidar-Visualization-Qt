#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStringList>
#include <QMessageBox>
#include <QVector>
#include <QFileDialog>
#include <QTime>
#include <QThread>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGenericMatrix>
#include <QMatrix>
#include <QtMath>
#include <algorithm>
#include "exportchoice.h"
#include "exportimage.h"
#include "exportvideo.h"
QVector <QVector < QVector < double > > > frames;
int currentFrameCount, amountOfFrames;
bool metadata=false;
QString metadataPath;
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->labelInfo->setVisible(false);
    ui->pushNext->setVisible(false);
    ui->pushPrevious->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector <double> normalizedNegative1To1(QVector <double> List, double json=0)
{
    QVector <double> listToReturn;
    double min = *std::min_element(List.constBegin(), List.constEnd());
    double max = *std::max_element(List.constBegin(), List.constEnd());
    double diffMaxMin = max - min;
    if (json!=0)
    {
        for(int i = 0; i<List.size();i++)
        {
            listToReturn.append(((List[i]+json-min)/(diffMaxMin))*2 - 1);
        }
    }
    else
    {
        for(int i = 0; i<List.size();i++)
        {
            listToReturn.append(((List[i]-min)/(diffMaxMin))*2 - 1);
        }
    }
    return listToReturn;
}/*
QVector <QVector <double>> quaternionToEuler(QVector <double> w,QVector <double> x,QVector <double> y,QVector <double> z)
{
    QVector <QVector <double>> rotation;
    for(int i = 0;i<w.length();i++)
    {
       QVector <double> rotationSingle;
       double sinr_cosp = 2 * (w[i] * x[i] + y[i] * z[i]);
       double cosr_cosp = 1 - 2 * (x[i] *x[i] + y[i] *y[i]);
       double roll = qAtan2(sinr_cosp,cosr_cosp);
       double sinp = 2 * (w[i] * y[i] - z[i] * x[i]);
       double pitch;
       if(abs(sinp)>=1)
       {
           if(sinp<0)
           {
               double pitch = -1* M_PI_2;
           }
           else if(sinp==0)
           {
               double pitch = 0* M_PI_2;
           }
           else
           {
               double pitch = 1 * M_PI_2;
           }
       }
       else
       {
           double pitch = qSin(sinp);
       }
      double siny_cosp = 2 * (w[i] * z[i] + x[i] * y[i]);
      double cosy_cosp = 1 - 2 * (y[i] *y[i] + z[i] *z[i]);
      double yaw = qAtan2(siny_cosp, cosy_cosp);
      rotationSingle.append(roll);
      rotationSingle.append(pitch);
      rotationSingle.append(yaw);
      rotation.append(rotationSingle);
      }
}*/
int MainWindow::readCSV(QStringList pathes)
{

    QVector<double> xList;
    QVector<double> yList;
    QVector<double> zList;
    QVector<QVector <double>> coordinates;
    frames.clear();
    ui->G->setEnabled(true);
    ui->G->setValue(2);
    if(metadata)
    {
        QString file_path = metadataPath;
        qDebug()<<file_path;
        qDebug()<<"po if";
        QFile file_obj(file_path);
        if(!file_obj.open(QIODevice::ReadOnly)){
            qDebug()<<"Failed to open "<<file_path;
            exit(1);
        }
        qDebug()<<"po if2";
        QTextStream file_text(&file_obj);
        QString json_string;
        json_string = file_text.readAll();
        file_obj.close();
        qDebug()<<"po if3";
        QByteArray json_bytes = json_string.toLocal8Bit();
        auto json_doc=QJsonDocument::fromJson(json_bytes);
        qDebug()<<"po if4";
        if(json_doc.isNull()){
            qDebug()<<"Failed to create JSON doc.";
            exit(2);
        }
        qDebug()<<"po if5";
        if(!json_doc.isArray()){
            qDebug() << "JSON doc is not an array.";
            exit(2);
        }

        QJsonArray json_array = json_doc.array();
        QVector <double> xPoses;
        QVector <double> yPoses;
        QVector <double> zPoses;
        QVector <double> wHeading;
        QVector <double> xHeading;
        QVector <double> yHeading;
        QVector <double> zHeading;
        for(int i=0; i< json_array.count(); ++i){
            xPoses.append(json_array.at(i).toObject().toVariantMap()["position"].toJsonObject().toVariantMap()["x"].toDouble());
            yPoses.append(json_array.at(i).toObject().toVariantMap()["position"].toJsonObject().toVariantMap()["y"].toDouble());
            zPoses.append(json_array.at(i).toObject().toVariantMap()["position"].toJsonObject().toVariantMap()["z"].toDouble());
            wHeading.append(json_array.at(i).toObject().toVariantMap()["heading"].toJsonObject().toVariantMap()["w"].toDouble());
            xHeading.append(json_array.at(i).toObject().toVariantMap()["heading"].toJsonObject().toVariantMap()["x"].toDouble());
            yHeading.append(json_array.at(i).toObject().toVariantMap()["heading"].toJsonObject().toVariantMap()["y"].toDouble());
            zHeading.append(json_array.at(i).toObject().toVariantMap()["heading"].toJsonObject().toVariantMap()["z"].toDouble());

        }
       // QVector<QVector<double>> translation{xPoses,yPoses,zPoses};
        //QVector<QVector<double>> rotation = quaternionToEuler(wHeading,xHeading,yHeading,zHeading);

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
            coordinates.append(normalizedNegative1To1(yList,yPoses[i]));
            coordinates.append(normalizedNegative1To1(zList,zPoses[i]));
            frames.append(coordinates);
            coordinates.clear();
            ui->G->setValue(((i+1)*100)/(pathes.size()));
            qApp->processEvents();
        }
        currentFrameCount = 1;
        amountOfFrames = frames.size();
        return 0;

    }
    else
    {
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
            coordinates.append(normalizedNegative1To1(zList));
            coordinates.append(normalizedNegative1To1(yList));
            frames.append(coordinates);
            coordinates.clear();
            ui->G->setValue(((i+1)*100)/(pathes.size()));
            qApp->processEvents();
        }
        currentFrameCount = 1;
        amountOfFrames = frames.size();
        return 0;
    }

}

void MainWindow::on_pushButton_Load_clicked()
{
    QStringList pathes = ui->linePath->text().split(',');
    ui->labelInfo->setVisible(false);
    if(readCSV(pathes))
    {
        ui->labelInfo->setText("Porażka");
        ui->labelInfo->setVisible(true);
        ui->pushButton_Generate->setEnabled(false);
        ui->pushButtonExport->setEnabled(false);
        ui->pushButtonPlay->setEnabled(false);
        ui->checkBoxCurrentFrame->setEnabled(false);
        ui->verticalSliderColorDepth->setEnabled(false);
        ui->verticalSliderFrames->setEnabled(false);
    }
    else
    {
        ui->labelInfo->setText("Sukces");
        ui->labelInfo->setVisible(true);
        ui->pushButton_Generate->setEnabled(true);
        ui->pushButtonExport->setEnabled(true);
        ui->pushButtonPlay->setEnabled(true);
        ui->checkBoxCurrentFrame->setEnabled(true);
    }
}



void MainWindow::on_OpenFile_clicked()
{
    QStringList filenames = QFileDialog::getOpenFileNames(
                this,
                tr("Otwórz pliki"),
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

    ui->verticalSliderColorDepth->setEnabled(true);
    ui->verticalSliderFrames->setEnabled(true);
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
void MainWindow::nextFrame()
{
    currentFrameCount+=1;
    ui->OpenGLWidget->takeVectors(frames[currentFrameCount-1][0],frames[currentFrameCount-1][1],frames[currentFrameCount-1][2]);
    qApp->processEvents();

}
void MainWindow::previousFrame()
{
    currentFrameCount-=1;
    ui->OpenGLWidget->takeVectors(frames[currentFrameCount-1][0],frames[currentFrameCount-1][1],frames[currentFrameCount-1][2]);
    qApp->processEvents();
}

void MainWindow::on_pushPrevious_clicked()
{
    MainWindow::previousFrame();
    ui->pushNext->setEnabled(true);
    ui->labelFrame->setText(QString::number(currentFrameCount)+"/"+QString::number(amountOfFrames));
    if(currentFrameCount==1)
    {
        ui->pushPrevious->setEnabled(false);
    }
}

void MainWindow::on_pushNext_clicked()
{
    MainWindow::nextFrame();
    ui->pushPrevious->setEnabled(true);
    ui->labelFrame->setText(QString::number(currentFrameCount)+"/"+QString::number(amountOfFrames));
    if(currentFrameCount==amountOfFrames)
    {
        ui->pushNext->setEnabled(false);
    }
}

void MainWindow::on_pushButtonExport_clicked()
{
    exportchoice = new exportChoice(this);
    exportchoice->setAttribute(Qt::WA_DeleteOnClose);
    exportchoice->exec();
    if(exportchoice->getChoice())
    {
        exportvideo = new exportVideo(this);
        exportvideo->setAttribute(Qt::WA_DeleteOnClose);
        exportvideo->exec();
        exportVideoFile();
    }
    else
    {
        exportimage = new exportImage(this);
        exportimage->setAttribute(Qt::WA_DeleteOnClose);
        exportimage->exec();
        exportImages();
    }
}

void MainWindow::on_verticalSliderColorDepth_valueChanged(int value)
{
    ui->OpenGLWidget->changeColorDepth(value);
    ui->OpenGLWidget->takeVectors(frames[currentFrameCount-1][0],frames[currentFrameCount-1][1],frames[currentFrameCount-1][2]);
}

void MainWindow::on_verticalSliderFrames_valueChanged(int value)
{
    ui->labelFrames->setNum(value);
}

void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void MainWindow::on_pushButtonPlay_clicked()
{
    int framesPerSec = ui->verticalSliderFrames->value();
    int msInterval = 1000/framesPerSec;
    bool playBegin = ui->checkBoxCurrentFrame->isChecked();
    if(playBegin){}
    else
    {
        currentFrameCount=1;
        ui->OpenGLWidget->takeVectors(frames[currentFrameCount-1][0],frames[currentFrameCount-1][1],frames[currentFrameCount-1][2]);
        ui->labelFrame->setText(QString::number(currentFrameCount)+"/"+QString::number(amountOfFrames));
        ui->pushPrevious->setEnabled(true);
        ui->pushNext->setEnabled(true);
    }
    int originalFrameCount = currentFrameCount;
    ui->pushNext->setEnabled(false);
    ui->pushPrevious->setEnabled(false);
    for(int i = currentFrameCount;i<amountOfFrames;i++)
    {
        MainWindow::nextFrame();
        ui->labelFrame->setText(QString::number(currentFrameCount)+"/"+QString::number(amountOfFrames));
        delay(msInterval);
    }
    delay(500);
    currentFrameCount = originalFrameCount;
    ui->labelFrame->setText(QString::number(currentFrameCount)+"/"+QString::number(amountOfFrames));
    ui->OpenGLWidget->takeVectors(frames[currentFrameCount-1][0],frames[currentFrameCount-1][1],frames[currentFrameCount-1][2]);
    ui->pushNext->setEnabled(true);
    ui->pushPrevious->setEnabled(true);
    if(currentFrameCount==amountOfFrames)
    {
        ui->pushNext->setEnabled(false);
    }
    else if(currentFrameCount==1)
    {
        ui->pushPrevious->setEnabled(false);
    }



}
void MainWindow::exportImages()
{
    ui->pushNext->setEnabled(false);
    ui->pushPrevious->setEnabled(false);
    QStringList data = exportimage->getDataExport();
    QString path = ""+data[0];
    QString file = ""+data[1];
    QString format = ""+data[2];
    QString slash = "/";
    for(int i = 0;i<amountOfFrames;i++)
    {
        ui->OpenGLWidget->takeVectors(frames[i][0],frames[i][1],frames[i][2]);
        ui->labelFrame->setText(QString::number(i+1)+"/"+QString::number(amountOfFrames));
        //qDebug()<<(""+path+slash+file+QString::number(i)+format);
        ui->OpenGLWidget->grabFramebuffer().save((""+path+slash+file+QString::number(i)+format));
        qApp->processEvents();
    }
    ui->labelFrame->setText(QString::number(currentFrameCount)+"/"+QString::number(amountOfFrames));
    ui->OpenGLWidget->takeVectors(frames[currentFrameCount-1][0],frames[currentFrameCount-1][1],frames[currentFrameCount-1][2]);
    ui->pushNext->setEnabled(true);
    ui->pushPrevious->setEnabled(true);
    if(currentFrameCount==amountOfFrames)
    {
        ui->pushNext->setEnabled(false);
    }
    else if(currentFrameCount==1)
    {
        ui->pushPrevious->setEnabled(false);
    }

};
QString whatZero(int i) // Images are saving with names 001, 002.. 010.. 012... 111, so we have to add zeros
{
    if (i<9)
    {
        return QString("00");
    }
    else if (i<99)
    {
        return QString("0");
    }
    else
    {
        return QString("");
    }
}
void MainWindow::exportVideoFile()
{
    ui->pushNext->setEnabled(false);
    ui->pushPrevious->setEnabled(false);
    QStringList data = exportvideo->getDataExport();
    QString path = ""+data[0];
    QString imagesFileName = ""+data[1];
    QString out = ""+data[1] + data[2];
    QString formatTemporaryImages = ".png";
    QString framesPerSecond =""+ data[3];
    QString slash = "/";
    // We're creating temporary image files in order to make video file by ffmpeg, after all we will remove them.
    for(int i = 0;i<amountOfFrames;i++)
    {
        ui->OpenGLWidget->takeVectors(frames[i][0],frames[i][1],frames[i][2]);
        ui->labelFrame->setText(QString::number(i+1)+"/"+QString::number(amountOfFrames));
        ui->OpenGLWidget->grabFramebuffer().save(""+path+slash+imagesFileName+whatZero(i)+QString::number(i+1)+formatTemporaryImages);
        qApp->processEvents();
    }
    ui->labelFrame->setText(QString::number(currentFrameCount)+"/"+QString::number(amountOfFrames));
    ui->OpenGLWidget->takeVectors(frames[currentFrameCount-1][0],frames[currentFrameCount-1][1],frames[currentFrameCount-1][2]);
    ui->pushNext->setEnabled(true);
    ui->pushPrevious->setEnabled(true);
    if(currentFrameCount==amountOfFrames)
    {
        ui->pushNext->setEnabled(false);
    }
    else if(currentFrameCount==1)
    {
        ui->pushPrevious->setEnabled(false);
    }
    QString ffmpegPath= "D:/QtProjects/ffmpeg/bin/ffmpeg.exe";

    QStringList arguments;
    arguments<<"-r"<<framesPerSecond<<"-i"<<(""+path+slash+imagesFileName+"%03d"+formatTemporaryImages)<< "-preset" << "veryslow" <<""+path+slash+out;
    for(int i=0;i<arguments.size();i++)
    {
        qDebug() << arguments[i]; // Checking that arguments loaded correctly.
    }
    QProcess *ffmpegProc = new QProcess(this);
    ffmpegProc->start(ffmpegPath, arguments);
    ffmpegProc->waitForFinished();
    //Removing temporary files
    for(int i = 0; i<amountOfFrames;i++)
    {
       remove((""+path+slash+imagesFileName+whatZero(i)+QString::number(i+1)+formatTemporaryImages).toLocal8Bit().data()); //remove handling only with format char, so we have to map QString to char.
    }
};

void MainWindow::on_pushButton_Options_clicked()
{
    options = new Options(this);
    options->setAttribute(Qt::WA_DeleteOnClose);
    options->exec();
    metadata = options->getIsChecked();
    metadataPath = options->getData();
}
