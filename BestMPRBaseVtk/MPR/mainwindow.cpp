#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>


#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDICOMImageReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkOutlineFilter.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkPolyDataNormals.h>
#include <vtkContourFilter.h>
#include <vtkSmartPointer.h>



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

void MainWindow::openFile(QString dir)
{
    readDicomImageNormal(dir.toLocal8Bit().data());
    readDicomImageBPP(dir.toLocal8Bit().data());
    ui->groupBox->setEnabled(true);
}
/**
 * @brief MainWindow::on_pushButton_ReadDicom_clicked
 * 读取Dicom文件槽函数
 */
void MainWindow::on_pushButton_ReadDicom_clicked()
{
    this->openFile(QString("D:\\00_Code\\ST0\\SE2"));
}
/**
 * @brief MainWindow::readDicomImage
 * @param url
 * 读取Dicom文件,使用官方标准vtkImageViewer2
 * 这里将准备改为体渲染或面渲染
 */
void MainWindow::readDicomImageNormal(const char *url)
{
    //读取Dicom文件

    vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
    reader->SetDirectoryName(url);
    reader->SetDataSpacing(3.2, 1.5, 1.5);
    reader->Update();

    qDebug()  << reader->GetPixelRepresentation() << reader->GetNumberOfComponents() << reader->GetNumberOfScalarComponents();





    //这是一个过滤器，官方翻译如下
    //vtkContourFilter是一个过滤器，它将任何数据集作为输入，并在输出等值面和/或等值线上生成。
    //输出的确切形式取决于输入数据的维数。 由3D单元格组成的数据将生成等值面，由2D单元格组成的数据将生成等值线，
    //由1D或0D单元格组成的数据将生成等点。 如果输入维度是混合的，输出类型的组合是可能的。

    //若要使用此筛选器，必须指定一个或多个轮廓值。 您可以使用SetValue()方法来指定每个轮廓值，也可以使用GenerateValues()来生成一系列均匀间隔的轮廓。
    //还可以通过使用vtkScalarTree来加速这个过滤器的操作(以额外的内存为代价)。 标量树用于快速定位包含轮廓曲面的单元。 这是特别有效的，如果多个轮廓被提取。
    //如果您想要使用标量树，请调用方法UseScalarTreeOn()。

    vtkSmartPointer<vtkContourFilter> skinExtractor = vtkSmartPointer<vtkContourFilter>::New();
    skinExtractor->SetInputConnection(reader->GetOutputPort());
    skinExtractor->SetValue(0, 500);

    //vtkPolyDataNormals是一个为多边形网格计算点和/或单元法线的过滤器。
    //用户通过设置ComputeCellNormals和ComputePointNormals标志来指定他们是否希望计算点和/或单元格法线。

    vtkSmartPointer<vtkPolyDataNormals> skinNormals = vtkSmartPointer<vtkPolyDataNormals>::New();
    skinNormals->SetInputConnection(skinExtractor->GetOutputPort());
    skinNormals->SetFeatureAngle(60.0);


    vtkSmartPointer<vtkPolyDataMapper> skinMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    skinMapper->SetInputConnection(skinNormals->GetOutputPort());
    skinMapper->ScalarVisibilityOff();

    vtkSmartPointer<vtkActor> skin = vtkSmartPointer<vtkActor>::New();
    skin->SetMapper(skinMapper);

    vtkSmartPointer<vtkRenderer> aRenderer = vtkSmartPointer<vtkRenderer>::New();
    aRenderer->SetBackground(0, 0, 0);
    aRenderer->ResetCameraClippingRange();
    ui->openGLWidget->renderWindow()->AddRenderer(aRenderer);

    aRenderer->AddActor(skin);

    ui->openGLWidget->renderWindow()->Render();


}
/**
 * @brief MainWindow::readDicomImageBPP
 * @param url
 * 读取Dicom文件 使用自定义的BPPMPRWidget
 */
void MainWindow::readDicomImageBPP(const char *url)
{
    vtkSmartPointer<vtkDICOMImageReader> render = vtkSmartPointer<vtkDICOMImageReader>::New();
    render->SetDirectoryName(url);
    render->Update();

    qDebug() << render->GetBitsAllocated() << render->GetPixelRepresentation();

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

/**
 * @brief MainWindow::on_pushButton_ReadDicom_2_clicked
 * 读取文件夹
 */
void MainWindow::on_pushButton_ReadDicom_2_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Folder"),"D:\\00_Code\\ST0\\SE2",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    if(!dir.isEmpty())
    {
        this->openFile(dir);
    }
}

