#include "myimagereslicewindow.h"
#include "ui_myimagereslicewindow.h"
#include <QFileDialog>
#include <QtDebug>
MyImageResliceWindow::MyImageResliceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyImageResliceWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("MPR Demo And Test");
    reader = vtkDICOMImageReader::New();
    reader->SetDirectoryName("D:\\00_Code\\ST0\\SE2");

    for(int i = 0;i<3;i++)
    {
        reslice[i] = vtkSmartPointer<vtkImageReslice>::New();
        resliceAxes[i] = vtkSmartPointer<vtkMatrix4x4>::New();
        colorTable[i] = vtkSmartPointer<vtkLookupTable>::New();
        colorMap[i] = vtkSmartPointer<vtkImageMapToColors>::New();
        imgActor[i] = vtkSmartPointer<vtkImageActor>::New();
        renderer[i] = vtkSmartPointer<vtkRenderer>::New();
    }
}

MyImageResliceWindow::~MyImageResliceWindow()
{
    delete ui;
}

void MyImageResliceWindow::readDicom(QString temp)
{
    reader->SetDirectoryName(temp.toLocal8Bit().data());                            //设置文件夹路径
    reader->Update();                                                               //更新
    reader->GetOutput()->GetExtent(this->extent);                                   //获取图像序列范围
    reader->GetOutput()->GetSpacing(this->spacing);                                 //获取数据间距
    reader->GetOutput()->GetOrigin(this->origin);                                   //获取原点

    center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);             //获取中心点
    center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);             //获取中心点
    center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);             //获取中心点
}

void MyImageResliceWindow::initImageForm()
{
    resliceAxes[0]->DeepCopy(axialElements);
    resliceAxes[1]->DeepCopy(sagittalElements);
    resliceAxes[2]->DeepCopy(coronalElements);
    for (int i = 0; i< 3; i++ ) {
        reslice[i]->SetInputConnection(reader->GetOutputPort());                    //设置数据输入源
        reslice[i]->SetOutputDimensionality(2);                                     //设置输出为一个切片，而不是一个卷
        reslice[i]->SetResliceAxes(resliceAxes[i]);                                 //设置矩阵
        reslice[i]->SetResliceAxesOrigin(center[0],center[1],center[2]);            //设置切片中心点
        reslice[i]->SetInterpolationModeToLinear();                                 //设置切面算法的插值方式线性插值
        colorTable[i]->SetRange(0, 1000);                                           //设置颜色表范围
        colorTable[i]->SetValueRange(0.0, 1.0);                                     //设置颜色表精度
        colorTable[i]->SetSaturationRange(0.0, 0.0);                                //设置曝光范围 ？
        colorTable[i]->SetRampToLinear();                                           //设置颜色表为线性
        colorTable[i]->Build();                                                     //构建
        colorMap[i]->SetLookupTable(colorTable[i]);                                 //设置颜色表
        colorMap[i]->SetInputConnection(reslice[i]->GetOutputPort());               //设置图像数据
        imgActor[i]->GetMapper()->SetInputConnection(colorMap[i]->GetOutputPort()); //添加映射器
        renderer[i]->AddActor(imgActor[i]);                                         //添加演员
        renderer[i]->SetBackground(0.0, 0.0, 0.0);                                  //设置背景
    }
    ui->openGLWidget_1->renderWindow()->AddRenderer(renderer[0]);                   //UI渲染窗口添加渲染器
    ui->openGLWidget_1->renderWindow()->Render();                                   //开始渲染
    ui->openGLWidget_2->renderWindow()->AddRenderer(renderer[1]);                   //UI渲染窗口添加渲染器
    ui->openGLWidget_2->renderWindow()->Render();                                   //开始渲染
    ui->openGLWidget_3->renderWindow()->AddRenderer(renderer[2]);                   //UI渲染窗口添加渲染器
    ui->openGLWidget_3->renderWindow()->Render();                                   //开始渲染

}

/**
 * @brief MyImageResliceWindow::on_pushButton_reader_clicked
 * 读取Dicom文件
 */
void MyImageResliceWindow::on_pushButton_reader_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Folder"),"D:\\00_Code\\ST0\\SE2",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    if(!dir.isEmpty())
    {
        readDicom(dir);
        initImageForm();
    }
}


void MyImageResliceWindow::on_pushButton_reader_2_clicked()
{
    readDicom(QString("D:\\00_Code\\ST0\\SE2"));
    initImageForm();

    update();
}

/**
 * @brief MyImageResliceWindow::on_pushButton_SetDirection_clicked
 * 切换切面
 */
void MyImageResliceWindow::on_pushButton_SetDirection_clicked()
{

}

