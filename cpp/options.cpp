#include "options.h"
#include "ui_options.h"

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
}

Options::~Options()
{
    delete ui;
}

void Options::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
    ui->lineEditPath->setEnabled(true);
    ui->pushButtonChoose->setEnabled(true);
    }
    else
    {
        ui->lineEditPath->setEnabled(false);
        ui->pushButtonChoose->setEnabled(false);
    }
}
void Options::on_pushButtonApply_clicked()
{
    metaData = ui->checkBox->isChecked();
    metadataPath = ui->lineEditPath->text();
    this->close();
}

void Options::on_pushButtonChoose_clicked()
{
    QString metadataPath = QFileDialog::getOpenFileName(this,tr("Wybierz plik z metadanymi"),
                                                           "",
                                                           "(*.json)"
                                                           );
    ui->lineEditPath->clear();
    ui->lineEditPath->insert(metadataPath);
}
QString Options::getData()
{
    return metadataPath;
}
bool Options::getIsChecked()
{
    return metaData;
}
