#include "Window.h"
#include "Viewer.h"

Window::Window():QWidget()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 10);
    slider->setValue(3);
    
    Viewer *viewer = new Viewer();
    
    connect(slider, SIGNAL(valueChanged(int)), viewer, SLOT(setIter(int)));
    
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(viewer);
    layout->addWidget(slider);
    setLayout(layout);
    
}
