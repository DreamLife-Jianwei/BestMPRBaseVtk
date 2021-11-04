#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkDICOMImageReader.h>
#include <vtkImageViewer2.h>
#include <bppmprwidget.h>
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
private:
    Ui::MainWindow *ui;


    BPPMPRWidget* mBPPMPRWidget = nullptr;


};

#endif // MAINWINDOW_H
