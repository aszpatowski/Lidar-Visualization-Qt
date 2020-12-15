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
    QString folderpath = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                           "C://",
                                                           QFileDialog::ShowDirsOnly
                                                           | QFileDialog::DontResolveSymlinks);
    ui->lineEdit->clear();
    ui->lineEdit->insert(folderpath);
}
