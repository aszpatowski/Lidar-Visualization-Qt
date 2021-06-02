#include "exportvideo.h"
#include "ui_exportvideo.h"
#include <QtDebug>
exportVideo::exportVideo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exportVideo)
{
    ui->setupUi(this);
}

exportVideo::~exportVideo()
{
    delete ui;
}

void exportVideo::on_verticalSliderFrames_valueChanged(int value)
{
    ui->labelFrames->setNum(value);
}

void exportVideo::on_pushButton_clicked()
{
    QString folderpath = QFileDialog::getExistingDirectory(this, tr("Wybierz folder"),
                                                           "",
                                                           QFileDialog::ShowDirsOnly
                                                           | QFileDialog::DontResolveSymlinks);
    ui->lineEditFolder->clear();
    ui->lineEditFolder->insert(folderpath);
}

void exportVideo::on_pushButtonExport_clicked()
{
    path = ui->lineEditFolder->text();
    filename = ui->lineEditFileName->text();
    format = ui->comboBoxFormat->currentText();
    framesPerSecond = ui->verticalSliderFrames->value();
    if(ui->checkBox->isChecked())
    {
        ffmpegpath =ui->lineEditFFMPEG->text();
    }
    else
    {
        ffmpegpath = "ffmpeg";
    }
    this->close();

}


void exportVideo::on_pushButton_2_clicked()
{
    QString ffmpegpath = QFileDialog::getOpenFileName(this,tr("Wybierz plik ffmpeg.exe"),
                                                           "",
                                                           "ffmpeg (*.exe)"
                                                           );
    ui->lineEditFFMPEG->clear();
    ui->lineEditFFMPEG->insert(ffmpegpath);
}

void exportVideo::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ffmpegpath =ui->lineEditFFMPEG->text();
        ui->lineEditFFMPEG->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
    }
    else
    {
        ffmpegpath = "ffmpeg";
        ui->lineEditFFMPEG->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
    }
}
