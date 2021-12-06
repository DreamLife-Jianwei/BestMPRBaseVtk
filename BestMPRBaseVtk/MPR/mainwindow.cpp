#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BestMPRWidget");
    mBPPMPRWidget1 = new BPPMPRWidget(this);
    mBPPMPRWidget1->setGeometry(0,0,350,350);

    mBPPMPRWidget2 = new BPPMPRWidget(this);
    mBPPMPRWidget2->setGeometry(350,0,350,350);

    mBPPMPRWidget3 = new BPPMPRWidget(this);
    mBPPMPRWidget3->setGeometry(0,350,350,350);

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
    readDicomImageNormal("D:\\00_Code\\ST0\\SE2");
    readDicomImageBPP("D:\\00_Code\\ST0\\SE2");
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

    mBPPMPRWidget1->setInputData(render->GetOutput());
    mBPPMPRWidget1->setSliceOrientation(2);
    mBPPMPRWidget1->render();


    mBPPMPRWidget2->setInputData(render->GetOutput());
    mBPPMPRWidget2->setSliceOrientation(0);
    mBPPMPRWidget2->render();


    mBPPMPRWidget3->setInputData(render->GetOutput());
    mBPPMPRWidget3->setSliceOrientation(1);
    mBPPMPRWidget3->render();

}
/**
 * @brief on_pushButton_ColorWindow_clicked
 * 获取窗宽
 */
void MainWindow::on_pushButton_ColorWindow_clicked()
{
    ui->pushButton_ColorWindow->setText(QString::number(mBPPMPRWidget1->getColorWindow(),'f',10));
}
/**
 * @brief on_pushButton_ColorLevel_clicked
 * 获取窗位
 */
void MainWindow::on_pushButton_ColorLevel_clicked()
{
    ui->pushButton_ColorLevel->setText(QString::number(mBPPMPRWidget1->getColorLevel(),'f',10));
}

/**
 * @brief MainWindow::on_horizontalSlider_ColorWindow_valueChanged
 * @param value
 * 修改窗宽测试
 */
void MainWindow::on_horizontalSlider_ColorWindow_valueChanged(int value)
{
    mBPPMPRWidget1->setColorWindow(value);
    mBPPMPRWidget1->update();

    mBPPMPRWidget2->setColorWindow(value);
    mBPPMPRWidget2->update();

    mBPPMPRWidget3->setColorWindow(value);
    mBPPMPRWidget3->update();

    viewer->SetColorWindow(value);
    viewer->Render();
}
/**
 * @brief MainWindow::on_horizontalSlider_ColorLevel_valueChanged
 * @param value
 * 修改窗位测试
 */
void MainWindow::on_horizontalSlider_ColorLevel_valueChanged(int value)
{
    mBPPMPRWidget1->setColorLevel(value);
    mBPPMPRWidget1->update();

    mBPPMPRWidget2->setColorLevel(value);
    mBPPMPRWidget2->update();

    mBPPMPRWidget3->setColorLevel(value);
    mBPPMPRWidget3->update();

    viewer->SetColorLevel(value);
    viewer->Render();

}
/**
 * @brief on_pushButton_Slicechange_clicked
 * 切换切面显示
 */

void MainWindow::on_pushButton_Slicechange_clicked()
{
    int orientation = mBPPMPRWidget1->getSliceOrientation();
    orientation++;
    if(orientation == 3)
        orientation = 0;
    viewer->SetSliceOrientation(orientation);
    mBPPMPRWidget1->setSliceOrientation(orientation);


}
/**
 * @brief MainWindow::on_pushButton_Slicerange_clicked
 * 获取图像序列范围
 */
void MainWindow::on_pushButton_Slicerange_clicked()
{
    int* range = mBPPMPRWidget1->getSliceRange();
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
    mBPPMPRWidget1->setSlice(value);
    viewer->SetSlice(value);
}

/**
 * @brief MainWindow::on_pushButton_GetSize_clicked
 * 获取尺寸
 */
void MainWindow::on_pushButton_GetSize_clicked()
{
    int* msize = mBPPMPRWidget1->getSize();
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
    int* mpositon = mBPPMPRWidget1->getPosition();
    ui->pushButton_Position->setText("X: " + QString::number(mpositon[0],10) + "\nY: " + QString::number(mpositon[1],10));
}

/**
 * @brief MainWindow::on_spinBox_width_valueChanged
 * @param arg1
 * 宽度改变
 */
void MainWindow::on_spinBox_width_valueChanged(int arg1)
{
    mBPPMPRWidget1->setSize(arg1,ui->spinBox_height->value());
}

/**
 * @brief MainWindow::on_spinBox_height_valueChanged
 * @param arg1
 * 高度改变
 */
void MainWindow::on_spinBox_height_valueChanged(int arg1)
{
    mBPPMPRWidget1->setSize(ui->spinBox_width->value(),arg1);
}

/**
 * @brief MainWindow::on_pushButton_MPRPosition_clicked
 * MPR定位显示
 */
void MainWindow::on_pushButton_MPRPosition_clicked()
{

}


void MainWindow::on_pushButton_Slicerange_2_clicked()
{
    int* range = mBPPMPRWidget2->getSliceRange();
    ui->pushButton_Slicerange_2->setText(QString::number(range[0],10) + " - " + QString::number(range[1],10));
    ui->horizontalSlider_SliceRange_2->setMinimum(range[0]);
    ui->horizontalSlider_SliceRange_2->setMaximum(range[1]);
    ui->horizontalSlider_SliceRange_2->setValue(range[0]);
}


void MainWindow::on_pushButton_Slicerange_3_clicked()
{
    int* range = mBPPMPRWidget3->getSliceRange();
    ui->pushButton_Slicerange_3->setText(QString::number(range[0],10) + " - " + QString::number(range[1],10));
    ui->horizontalSlider_SliceRange_3->setMinimum(range[0]);
    ui->horizontalSlider_SliceRange_3->setMaximum(range[1]);
    ui->horizontalSlider_SliceRange_3->setValue(range[0]);
}


void MainWindow::on_horizontalSlider_SliceRange_2_valueChanged(int value)
{
    mBPPMPRWidget2->setSlice(value);
}


void MainWindow::on_horizontalSlider_SliceRange_3_valueChanged(int value)
{
    mBPPMPRWidget3->setSlice(value);
}


void MainWindow::on_pushButton_Slicechange_2_clicked()
{
    int orientation = mBPPMPRWidget2->getSliceOrientation();
    orientation++;
    if(orientation == 3)
        orientation = 0;
    mBPPMPRWidget2->setSliceOrientation(orientation);
}


void MainWindow::on_pushButton_Slicechange_3_clicked()
{
    int orientation = mBPPMPRWidget3->getSliceOrientation();
    orientation++;
    if(orientation == 3)
        orientation = 0;
    mBPPMPRWidget3->setSliceOrientation(orientation);
}

