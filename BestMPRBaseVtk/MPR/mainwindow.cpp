#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BestMPRWidget");
    mBPPMPRWidget = new BPPMPRWidget(this);
    mBPPMPRWidget->setGeometry(0,0,600,350);

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
    readDicomImageNormal("D:\\00_Code\\CT\\CT.1.2.840.113619.2.290.3.151673680.426.1473208896.505.18.dcm");
    readDicomImageBPP("D:\\00_Code\\CT\\CT.1.2.840.113619.2.290.3.151673680.426.1473208896.505.18.dcm");
}
/**
 * @brief MainWindow::readDicomImage
 * @param url
 * 读取Dicom文件
 */
void MainWindow::readDicomImageNormal(const char *url)
{
    vtkSmartPointer<vtkDICOMImageReader> render = vtkSmartPointer<vtkDICOMImageReader>::New();
    render->SetFileName(url);
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
    render->SetFileName(url);
    render->Update();
//    vtkSmartPointer<ImagePipeLine> viewer = vtkSmartPointer<ImagePipeLine>::New();
//    viewer->setInputData(render->GetOutput());
//    viewer->setRenderWindow(mBPPMPRWidget->renderWindow());
//    viewer->render();

    mBPPMPRWidget->setInputData(render->GetOutput());
    mBPPMPRWidget->render();
}


void MainWindow::on_pushButton_ColorWindow_clicked()
{
    ui->pushButton_ColorWindow->setText(QString::number(mBPPMPRWidget->getColorWindow(),'f',10));
}


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
    mBPPMPRWidget->updateDisplayExtent();

    qDebug() <<"runing";
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
    viewer->UpdateDisplayExtent();
}

