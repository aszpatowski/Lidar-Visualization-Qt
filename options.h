#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QString>
namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT

private:
bool metaData = false;
QString metadataPath;

public:
    explicit Options(QWidget *parent = nullptr);
    ~Options();
    QString getData();
    bool getIsChecked();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_pushButtonApply_clicked();

    void on_pushButtonChoose_clicked();

private:
    Ui::Options *ui;
};

#endif // OPTIONS_H
