#ifndef EXPORTVIDEO_H
#define EXPORTVIDEO_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QString>
namespace Ui {
class exportVideo;
}

class exportVideo : public QDialog
{
    Q_OBJECT

public:
    explicit exportVideo(QWidget *parent = nullptr);
    ~exportVideo();

private slots:
    void on_verticalSliderFrames_valueChanged(int value);

    void on_pushButton_clicked();

private:
    Ui::exportVideo *ui;
};

#endif // EXPORTVIDEO_H
