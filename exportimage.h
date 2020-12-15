#ifndef EXPORTIMAGE_H
#define EXPORTIMAGE_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QString>
namespace Ui {
class exportImage;
}

class exportImage : public QDialog
{
    Q_OBJECT

public:
    explicit exportImage(QWidget *parent = nullptr);
    ~exportImage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::exportImage *ui;
};

#endif // EXPORTIMAGE_H
