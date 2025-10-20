#include <QApplication>
#include "drawingcanvas.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    
    DrawingCanvas w; 

    
    w.show();

    return a.exec();
}
