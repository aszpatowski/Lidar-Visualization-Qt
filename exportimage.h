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

private:
    QString path;
    QString filename;
    QString format;

public:
    explicit exportImage(QWidget *parent = nullptr);
    ~exportImage();
    QStringList getDataExport()
    {
        QStringList data;
        data.append(path);
        data.append(filename);
        data.append(format);
        return data;
    }
private slots:
    void on_pushButton_clicked();

    void on_pushButtonExport_clicked();
private:
    Ui::exportImage *ui;

};

#endif // EXPORTIMAGE_H
