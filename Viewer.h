#ifndef __Viewer_h__
#define __Viewer_h__

#include <QGLWidget>
#include <math.h>
#include <QSlider>
#include <QHBoxLayout>
#include <QFile>
#include "LNHHolder.h"
#include <QTextStream>
#include <math.h>
#include <QDir>



class Viewer : public QGLWidget
{
    Q_OBJECT

  public:
    Viewer();
    QSize minimumSizeHint() const; // min size of widget
    QSize sizeHint() const; // start size ideal of widget
    
  public slots:
    void setIter(int x); // slot to get a cange in slider and redefine the recursion

  protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void plotPicture(); // plots the picture
    void runChaikin(int numIter); // runs chaikin on the set to the number of iterations.
    void readFile(); // reads in the contents of MightyMax.boone
    LNHHolder* orig; // LNHHolder of the original points
    LNHHolder* current; // LNHHolder of the recursivly produced points
    LinkNodeHolder* cursor; // LinkNodeHolder* for work
    LinkNodeHolder* temp; // LinkNodeHolder* for work
    bool noIter; // true if iterations was 0
    void mousePressEvent(QMouseEvent* event); // reload files when clicked 
    
    int iter; // number of times to iterate
};

#endif