#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QColor>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QDebug>
#include <QVector>
#define RGB_MIN 1
#define RGB_MAX 255


class MyOpenGLWidget: public QOpenGLWidget, public QOpenGLFunctions // klasa to MyOpenGLWidget, a nazwa obiektu to OpenGLWidget
{
    Q_OBJECT
public:
    MyOpenGLWidget(QWidget *parent = nullptr);
    void takeVectors(QVector <double> x, QVector <double> y, QVector <double> z)
    {
        xList = x;
        yList = y;
        zList = z;
        loadedFile = true;
        repaint();
    }
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
private:
    void qColorToRGB(const QColor &C, float &r,float &g,float &b) const;
    float normalize_0_1(float val, float min, float max) const;
    double normalize_0_1d(double val, double min, double max) const;
    QVector <double> colorByDistance(double distance);
    QVector <double> xList,yList,zList;
    bool loadedFile = false;
};

#endif // MYOPENGLWIDGET_H
