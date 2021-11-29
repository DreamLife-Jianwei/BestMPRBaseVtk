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

    void readDicomImageBPP(const char* url);
    void on_pushButton_ColorWindow_clicked();

    void on_pushButton_ColorLevel_clicked();

    void on_horizontalSlider_ColorWindow_valueChanged(int value);

    void on_horizontalSlider_ColorLevel_valueChanged(int value);

private:
    Ui::MainWindow *ui;


    BPPMPRWidget* mBPPMPRWidget = nullptr;

    vtkSmartPointer<vtkImageViewer2> viewer;


};

#endif // MAINWINDOW_H
