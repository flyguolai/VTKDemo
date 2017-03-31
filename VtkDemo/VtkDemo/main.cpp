#include "VtkDemo.h"
#include <QtWidgets/QApplication>
#include "qfiledialog.h"
#include <QPushButton>
#include <QLabel>
#include "Graphics.h"

#ifndef INITIAL_OPENGL
#define INITIAL_OPENGL
#include<vtkAutoInit.h> 
VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType);
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    VtkDemo w;
    w.show();

    return a.exec();
}

