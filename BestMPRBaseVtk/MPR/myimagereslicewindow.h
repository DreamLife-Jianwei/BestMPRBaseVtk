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
#include "vtkCamera.h"
namespace Ui {
class MyImageResliceWindow;
}

class MyImageResliceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MyImageResliceWindow(QWidget *parent = nullptr);
    ~MyImageResliceWindow();


    /**
     * @brief readDicom
     * @param temp 文件路径
     * 设置读取文件夹
     */
    void readDicom(QString temp);
    /**
     * @brief initImageForm
     * 初始化流水线
     */
    void initImageForm();

private slots:
    /**
     * @brief on_pushButton_reader_clicked
     * 选择读取Dicom文件夹按钮槽函数
     */
    void on_pushButton_reader_clicked();
    /**
     * @brief on_pushButton_reader_2_clicked
     * 直接测试按钮槽函数
     */
    void on_pushButton_reader_2_clicked();
    /**
     * @brief on_pushButton_SetDirection_clicked
     * 切换切面显示槽函数
     */
    void on_pushButton_SetDirection_clicked();

private:
    Ui::MyImageResliceWindow *ui;

    int extent[6];          //序列范围
    double spacing[3];      //图像切片间距
    double origin[3];       //图像原点
    double center[3];       //物体中心点
    //轴状矩阵
    double axialElements[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    //矢状矩阵
    double sagittalElements [16] = {
        0, 0, -1, 0,
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, 1 };
    //冠状矩阵
    double coronalElements [16] = {
        1, 0, 0, 0,
        0, 0, -1, 0,
        0, -1, 0, 0,
        0, 0, 0, 1 };

    vtkSmartPointer<vtkDICOMImageReader> reader = nullptr;      //Dicom文件读取器
    vtkSmartPointer<vtkMatrix4x4> resliceAxes[3];               //vtk 4×4矩阵
    vtkSmartPointer<vtkImageReslice> reslice[3];                //vtkImageReslice切片类
    vtkSmartPointer<vtkLookupTable> colorTable[3];              //颜色映射表
    vtkSmartPointer<vtkImageMapToColors> colorMap[3];           //图像彩色映射
    vtkSmartPointer<vtkImageActor> imgActor[3];                 //图像Actor
    vtkSmartPointer<vtkRenderer> renderer[3];                   //图像渲染器
};

#endif // MYIMAGERESLICEWINDOW_H
