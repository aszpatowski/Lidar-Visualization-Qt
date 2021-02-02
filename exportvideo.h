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
private:
    QString path;
    QString filename;
    QString format;
    QString ffmpegpath;
    int framesPerSecond;

public:
    explicit exportVideo(QWidget *parent = nullptr);
    ~exportVideo();
    QStringList getDataExport()
    {
        QStringList data;
        data.append(path);
        data.append(filename);
        data.append(format);
        data.append(QString::number(framesPerSecond));
        return data;
    }

private slots:
    void on_verticalSliderFrames_valueChanged(int value);

    void on_pushButton_clicked();

    void on_pushButtonExport_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::exportVideo *ui;
};

#endif // EXPORTVIDEO_H
