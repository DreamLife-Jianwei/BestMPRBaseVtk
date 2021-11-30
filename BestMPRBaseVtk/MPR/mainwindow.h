#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkDICOMImageReader.h>
#include <vtkImageViewer2.h>
#include <bppmprwidget.h>
#include "imagepipeline.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /**
     * @brief on_pushButton_ReadDicom_clicked
     * 读取Dicom文件槽函数
     */
    void on_pushButton_ReadDicom_clicked();
    /**
     * @brief readDicomImage
     * @param url
     * 读取dicom文件
     */
    void readDicomImageNormal(const char* url);
    /**
     * @brief readDicomImageBPP
     * @param url
     * 读取Dicom文件
     */
    void readDicomImageBPP(const char* url);
    /**
     * @brief on_pushButton_ColorWindow_clicked
     * 获取窗宽
     */
    void on_pushButton_ColorWindow_clicked();
    /**
     * @brief on_pushButton_ColorLevel_clicked
     * 获取窗位
     */
    void on_pushButton_ColorLevel_clicked();
    /**
     * @brief on_horizontalSlider_ColorWindow_valueChanged
     * @param value
     * 改变窗宽
     */
    void on_horizontalSlider_ColorWindow_valueChanged(int value);
    /**
     * @brief on_horizontalSlider_ColorLevel_valueChanged
     * @param value
     * 改变窗位
     */
    void on_horizontalSlider_ColorLevel_valueChanged(int value);
    /**
     * @brief on_pushButton_Slicechange_clicked
     * 切换切面显示
     */
    void on_pushButton_Slicechange_clicked();

    void on_pushButton_Slicerange_clicked();

    void on_horizontalSlider_SliceRange_valueChanged(int value);

private:
    Ui::MainWindow *ui;


    BPPMPRWidget* mBPPMPRWidget = nullptr;

    vtkSmartPointer<vtkImageViewer2> viewer;


};

#endif // MAINWINDOW_H
