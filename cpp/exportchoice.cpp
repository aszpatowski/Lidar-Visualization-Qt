#include "exportchoice.h"
#include "ui_exportchoice.h"
#include "exportimage.h"
#include "exportvideo.h"
exportChoice::exportChoice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exportChoice)
{
    ui->setupUi(this);
}

exportChoice::~exportChoice()
{
    delete ui;
}

void exportChoice::on_pushButtonVideo_clicked()
{
    choice = true;
    this->close();
}

void exportChoice::on_pushButtonImage_clicked()
{
    choice = false;
    this->close();
}

bool exportChoice::getChoice()
{
    return choice;
}

