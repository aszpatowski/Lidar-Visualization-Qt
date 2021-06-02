#include "myopenglwidget.h"

#include <QColor>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QtMath>
MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
:QOpenGLWidget {parent}
{
}
void MyOpenGLWidget::initializeGL()
{
    float r,g,b,a = normalize_0_1(255.0f,RGB_MIN,RGB_MAX);
    initializeOpenGLFunctions();
    qColorToRGB(Qt::black, r, g, b);
    glClearColor(r, g, b, a);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}
void MyOpenGLWidget::paintGL()
{
        if(loadedFile)
        {
            QVector <double> rgb;
            size_t length = xList.size();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            for (size_t i = 0;i<length;i++)
            {
                //glPointSize(1.0f);
                rgb = colorByDistance(qSqrt(zList[i]*zList[i]+xList[i]*xList[i]));
                glPointSize(1.0f);
                glColor3f(rgb[0],rgb[1],rgb[2]);
                glBegin(GL_POINTS);
                glVertex3d(xList[i],zList[i],yList[i]);
                glEnd();
            }
        }
        else
        {
        }
}
void MyOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MyOpenGLWidget::qColorToRGB(const QColor &C, float &r,float &g, float &b) const
{

    r = normalize_0_1(C.red(),RGB_MIN,RGB_MAX);
    g = normalize_0_1(C.green(),RGB_MIN,RGB_MAX);
    b = normalize_0_1(C.blue(),RGB_MIN,RGB_MAX);
}

float MyOpenGLWidget::normalize_0_1(float val, float min, float max) const
{
    return (val - min) / (max - min);
}

double MyOpenGLWidget::normalize_0_1d(double val, double min, double max) const
{
    return (val - min) / (max - min);
}


QVector <double> MyOpenGLWidget::colorByDistance(double distance)
{
    QVector <double> rgb;
    bool a = true;
    if(a)
    {
        if (abs(distance)<(colorIntensity+1)/2)
        {
            rgb<<1<<normalize_0_1d(abs(distance),0,(colorIntensity+1)/2)<<0;
            return rgb;
        }
        if (abs(distance)<(colorIntensity+0.4+1)/2)
        {
            rgb<<normalize_0_1d(abs(distance),(colorIntensity+0.4+1)/2,(colorIntensity+1)/2)<<1<<0;
            return rgb;
        }
        if (abs(distance)<(colorIntensity+0.7+1)/2)
        {
            rgb<<0<<1<<normalize_0_1d(abs(distance),(colorIntensity+0.4+1)/2,(colorIntensity+0.7+1)/2);
            return rgb;
        }
        if (abs(distance)<(colorIntensity+1+1)/2)
        {
            rgb<<0<<normalize_0_1d(abs(distance),(colorIntensity+1.2+1)/2,(colorIntensity+1+1)/2)<<1;
            return rgb;
        }
        else
        {
            rgb<<0<<0<<normalize_0_1d(abs(distance),1,(colorIntensity+1.2+1)/2);
            return rgb;
        }
    }
    else
    {
        if (distance<colorIntensity)
        {
            rgb<<1<<normalize_0_1d(distance,-1,colorIntensity)<<0;
            return rgb;
        }
        if (distance<colorIntensity+0.4)
        {
            rgb<<normalize_0_1d(distance,colorIntensity+0.4,colorIntensity)<<1<<0;
            return rgb;
        }
        if (distance<colorIntensity+0.7)
        {
            rgb<<0<<1<<normalize_0_1d(distance,colorIntensity+0.4,colorIntensity+0.7);
            return rgb;
        }
        if (distance<colorIntensity+1)
        {
            rgb<<0<<normalize_0_1d(distance,colorIntensity+1.2,colorIntensity+1)<<1;
            return rgb;
        }
        else
        {
            rgb<<0<<0<<normalize_0_1d(distance,1,colorIntensity+1.2);
            return rgb;
        }
    }
    }

