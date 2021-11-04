#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    readDicomImageNormal("D:\\00_Code\\CT\\CT.1.2.840.113619.2.290.3.151673680.426.1473208896.505.1.dcm");
    readDicomImageBPP("D:\\00_Code\\CT\\CT.1.2.840.113619.2.290.3.151673680.426.1473208896.505.1.dcm");
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
    vtkSmartPointer<vtkImageViewer2> viewer = vtkSmartPointer<vtkImageViewer2>::New();
    viewer->SetInputData(render->GetOutput());
    viewer->SetRenderWindow(ui->openGLWidget->renderWindow());
    viewer->Render();
}

void MainWindow::readDicomImageBPP(const char *url)
{
    vtkSmartPointer<vtkDICOMImageReader> render = vtkSmartPointer<vtkDICOMImageReader>::New();
    render->SetFileName(url);
    render->Update();
    vtkSmartPointer<vtkImageViewer2> viewer = vtkSmartPointer<vtkImageViewer2>::New();
    viewer->SetInputData(render->GetOutput());
    viewer->SetRenderWindow(mBPPMPRWidget->renderWindow());
    viewer->Render();
}

