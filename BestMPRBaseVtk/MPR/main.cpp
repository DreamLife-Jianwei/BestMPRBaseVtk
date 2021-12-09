
//Qt库
#include <QApplication>


//自己的库
#include "mainwindow.h"
#include "myimagereslicewindow.h"

//vtk
#include <vtkAutoInit.h>        //启动必须有
#include <vtkOutputWindow.h>    //控制台窗口

VTK_MODULE_INIT(vtkRenderingOpenGL2);               //注册使用，暂时还看不懂
VTK_MODULE_INIT(vtkInteractionStyle);               //注册使用，暂时还看不懂


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    MyImageResliceWindow w;
    w.show();

    return a.exec();
}



