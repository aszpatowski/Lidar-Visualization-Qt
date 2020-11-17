#include "myopenglwidget.h"

#include <QColor>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

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
            float r,g,b;
            size_t length = xList.size();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glPointSize(1.0f);
            glBegin(GL_POINTS);
            qColorToRGB(Qt::red, r, g, b);
            glColor3d(r,g,b);
            for (size_t i = 0;i<length;i++)
            {
                glVertex3d(xList[i],zList[i],yList[i]);
            }
            glEnd();

        }
        else
        {
        float r,g,b;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPointSize(5.0f);
        glBegin(GL_POINTS);
        qColorToRGB(Qt::green, r, g, b);
        glColor3f(r,g,b);
        glVertex3f(-0.5f,-0.5f,-0.5f);
        glVertex3f(0.5f,-0.5f,-0.5f);
        glEnd();
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

