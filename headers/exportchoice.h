#ifndef EXPORTCHOICE_H
#define EXPORTCHOICE_H

#include <QDialog>
#include "exportimage.h"
#include "exportvideo.h"
namespace Ui {
class exportChoice;
}

class exportChoice : public QDialog
{
    Q_OBJECT

public:
    explicit exportChoice(QWidget *parent = nullptr);
    ~exportChoice();
    bool getChoice();
private slots:
    void on_pushButtonVideo_clicked();

    void on_pushButtonImage_clicked();
public slots:

private:
    Ui::exportChoice *ui;
    exportImage *exportimage;
    exportVideo *exportvideo;
    bool choice;
};

#endif // EXPORTCHOICE_H
