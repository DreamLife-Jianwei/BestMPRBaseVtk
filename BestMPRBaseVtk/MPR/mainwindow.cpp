#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BestMPRWidget");
    mBPPMPRWidget = new BPPMPRWidget(this);
    mBPPMPRWidget->setGeometry(0,0,600,350);
    ui->groupBox->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief MainWindow::on_pushButton_ReadDicom_clicked
 * 读取Dicom文件槽函数
 */
void MainWindow::on_pushButton_ReadDicom_clicked()
{
    readDicomImageNormal("D:\\00_Code\\CT");
    readDicomImageBPP("D:\\00_Code\\CT");

    ui->groupBox->setEnabled(true);
}
/**
 * @brief MainWindow::readDicomImage
 * @param url
 * 读取Dicom文件
 */
void MainWindow::readDicomImageNormal(const char *url)
{
    vtkSmartPointer<vtkDICOMImageReader> render = vtkSmartPointer<vtkDICOMImageReader>::New();
    render->SetDirectoryName(url);
    render->Update();
    viewer = vtkSmartPointer<vtkImageViewer2>::New();
    viewer->SetInputData(render->GetOutput());
    viewer->SetRenderWindow(ui->openGLWidget->renderWindow());
    viewer->Render();
}
/**
 * @brief MainWindow::readDicomImageBPP
 * @param url
 * 读取Dicom文件
 */
void MainWindow::readDicomImageBPP(const char *url)
{
    vtkSmartPointer<vtkDICOMImageReader> render = vtkSmartPointer<vtkDICOMImageReader>::New();
    render->SetDirectoryName(url);
    render->Update();
    mBPPMPRWidget->setInputData(render->GetOutput());
    mBPPMPRWidget->render();
}
/**
 * @brief on_pushButton_ColorWindow_clicked
 * 获取窗宽
 */
void MainWindow::on_pushButton_ColorWindow_clicked()
{
    ui->pushButton_ColorWindow->setText(QString::number(mBPPMPRWidget->getColorWindow(),'f',10));
}
/**
 * @brief on_pushButton_ColorLevel_clicked
 * 获取窗位
 */
void MainWindow::on_pushButton_ColorLevel_clicked()
{
    ui->pushButton_ColorLevel->setText(QString::number(mBPPMPRWidget->getColorLevel(),'f',10));
}

/**
 * @brief MainWindow::on_horizontalSlider_ColorWindow_valueChanged
 * @param value
 * 修改窗宽测试
 */
void MainWindow::on_horizontalSlider_ColorWindow_valueChanged(int value)
{
    mBPPMPRWidget->setColorWindow(value);
    viewer->SetColorWindow(value);
    mBPPMPRWidget->update();
    viewer->Render();

}
/**
 * @brief MainWindow::on_horizontalSlider_ColorLevel_valueChanged
 * @param value
 * 修改窗位测试
 */
void MainWindow::on_horizontalSlider_ColorLevel_valueChanged(int value)
{
    mBPPMPRWidget->setColorLevel(value);
    viewer->SetColorLevel(value);
    viewer->Render();
    mBPPMPRWidget->update();
}
/**
 * @brief on_pushButton_Slicechange_clicked
 * 切换切面显示
 */
int orientation = 0;
void MainWindow::on_pushButton_Slicechange_clicked()
{
    viewer->SetSliceOrientation(orientation);
    mBPPMPRWidget->setSliceOrientation(orientation);

    if((orientation++) == 2)
    {
        orientation = 0;
    }
}

