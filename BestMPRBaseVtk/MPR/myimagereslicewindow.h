#ifndef MYIMAGERESLICEWINDOW_H
#define MYIMAGERESLICEWINDOW_H

#include <QWidget>
#include "QVTKOpenGLNativeWidget.h"
#include "vtkSmartPointer.h"
#include "vtkMetaImageReader.h"
#include "vtkImageData.h"
#include "vtkMatrix4x4.h"
#include "vtkImageReslice.h"
#include "vtkLookupTable.h"
#include "vtkImageMapToColors.h"
#include "vtkImageActor.h"
#include "vtkImageMapper3D.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleImage.h"
#include "vtkDICOMImageReader.h"
namespace Ui {
class MyImageResliceWindow;
}

class MyImageResliceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MyImageResliceWindow(QWidget *parent = nullptr);
    ~MyImageResliceWindow();



    void readDicom(QString temp);

    void initImageForm();

private slots:
    void on_pushButton_reader_clicked();

    void on_pushButton_reader_2_clicked();

    void on_pushButton_SetDirection_clicked();

private:
    Ui::MyImageResliceWindow *ui;

    int extent[6];          //序列范围
    double spacing[3];      //图像切片间距
    double origin[3];       //图像原点
    double center[3];

    vtkSmartPointer<vtkDICOMImageReader> reader = nullptr;      //Dicom文件读取器
    vtkSmartPointer<vtkMatrix4x4> resliceAxes[3];               //vtk 4×4矩阵
    vtkSmartPointer<vtkImageReslice> reslice[3];                //vtkImageReslice切片类
    vtkSmartPointer<vtkLookupTable> colorTable[3];              //颜色映射表
    vtkSmartPointer<vtkImageMapToColors> colorMap[3];           //图像彩色映射
    vtkSmartPointer<vtkImageActor> imgActor[3];                 //图像Actor
    vtkSmartPointer<vtkRenderer> renderer[3];                   //图像渲染器
};

#endif // MYIMAGERESLICEWINDOW_H
