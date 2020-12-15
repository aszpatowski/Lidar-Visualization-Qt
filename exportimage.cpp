#include "exportimage.h"
#include "ui_exportimage.h"

exportImage::exportImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exportImage)
{
    ui->setupUi(this);
}

exportImage::~exportImage()
{
    delete ui;
}

void exportImage::on_pushButton_clicked()
{
    QString folderpath = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                           "C://",
                                                           QFileDialog::ShowDirsOnly
                                                           | QFileDialog::DontResolveSymlinks);
    ui->lineEdit->clear();
    ui->lineEdit->insert(folderpath);
}
