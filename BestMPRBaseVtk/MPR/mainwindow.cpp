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
        orientation = 0;

}
/**
 * @brief MainWindow::on_pushButton_Slicerange_clicked
 * 获取图像序列范围
 */
void MainWindow::on_pushButton_Slicerange_clicked()
{
    int* range = mBPPMPRWidget->getSliceRange();
    ui->pushButton_Slicerange->setText(QString::number(range[0],10) + " - " + QString::number(range[1],10));
    ui->horizontalSlider_SliceRange->setMinimum(range[0]);
    ui->horizontalSlider_SliceRange->setMaximum(range[1]);
    ui->horizontalSlider_SliceRange->setValue(range[0]);
}

/**
 * @brief MainWindow::on_horizontalSlider_SliceRange_valueChanged
 * @param value
 * 设置序列值
 */
void MainWindow::on_horizontalSlider_SliceRange_valueChanged(int value)
{
    mBPPMPRWidget->setSlice(value);
    viewer->SetSlice(value);
}

/**
 * @brief MainWindow::on_pushButton_GetSize_clicked
 * 获取尺寸
 */
void MainWindow::on_pushButton_GetSize_clicked()
{
    int* msize = mBPPMPRWidget->getSize();
    ui->pushButton_GetSize->setText("Width: " + QString::number(msize[0],10) + "\nHeight: " + QString::number(msize[1],10));
    ui->spinBox_width->setValue(msize[0]);
    ui->spinBox_height->setValue(msize[1]);
}

/**
 * @brief MainWindow::on_pushButton_Position_clicked
 * 获取位置
 */
void MainWindow::on_pushButton_Position_clicked()
{
    int* mpositon = mBPPMPRWidget->getPosition();
    ui->pushButton_Position->setText("X: " + QString::number(mpositon[0],10) + "\nY: " + QString::number(mpositon[1],10));
}


void MainWindow::on_spinBox_width_valueChanged(int arg1)
{
    mBPPMPRWidget->setSize(arg1,ui->spinBox_height->value());
}


void MainWindow::on_spinBox_height_valueChanged(int arg1)
{
    mBPPMPRWidget->setSize(ui->spinBox_width->value(),arg1);
}

