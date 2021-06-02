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
    ui->lineEditFolder->clear();
    ui->lineEditFolder->insert(folderpath);
}

void exportImage::on_pushButtonExport_clicked()
{
    path = ui->lineEditFolder->text();
    filename = ui->lineEditFileName->text();
    format = ui->comboBoxFormat->currentText();
    this->close();

}


