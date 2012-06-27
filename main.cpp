#include <QApplication>
#include "Viewer.h"
#include "Window.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    
    Window window;
    window.setWindowTitle("Chaikin's Curves");
    window.show();

    return app.exec();
}
