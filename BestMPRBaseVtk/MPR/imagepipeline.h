#ifndef IMAGEPIPELINE_H
#define IMAGEPIPELINE_H

#include <QObject>
#include <vtkObject.h>

class vtkAlgorithm;
class vtkAlgorithmOutput;
class vtkImageActor;
class vtkImageData;
class vtkImageMapToWindowLevelColors;
class vtkInformation;
class vtkInteractorStyleImage;
class vtkRenderWindow;
class vtkRenderer;
class vtkRenderWindowInteractor;


class ImagePipeLine : public vtkObject
{

public:

    static ImagePipeLine* New();
    vtkTypeMacro(ImagePipeLine,vtkObject);

    virtual const char* getWindowName();                            //获取窗口名称

    virtual void render();                                          //开始渲染图像

    virtual vtkImageData* getInput();                               //获取输入数据

    virtual void setInputData(vtkImageData* in);                    //设置输入数据

    virtual void setInputConnection(vtkAlgorithmOutput* input);     //设置输入数据

    enum
     {  //切片方向
       SLICE_ORIENTATION_YZ = 0,
       SLICE_ORIENTATION_XZ = 1,
       SLICE_ORIENTATION_XY = 2
     };

    int getSliceOrientation();                                      //获取切片方向

    virtual void setSliceOrientation(int orientation);              //设置切片方向

    virtual void setSliceOrientationToXY();                         //设置切片方向

    virtual void setSliceOrientationToYZ();                         //设置切片方向

    virtual void setSliceOrientationToXZ();                         //设置切片方向

    virtual int getSlice();                                         //获取当前切片

    virtual void setSlice(int s);                                   //获取当前切片

    virtual void updateDisplayExtent();                             //更新显示范围

    virtual int getSliceMin();                                      //获取最小切片

    virtual int getSliceMax();                                      //获取最大切片

    virtual void getSliceRange(int range[2]);                       //获取切片范围

    virtual void getSliceRange(int& min, int& max);                 //获取切片范围

    virtual int* getSliceRange();                                   //获取切片范围

    virtual double getColorWindow();                                //获取窗宽

    virtual double getColorLevel();                                 //获取窗位

    virtual void setColorWindow(double s);                          //设置窗宽

    virtual void setColorLevel(double s);                           //设置窗位

    virtual void setDisplayId(void* a);                             //设置显示ID

    virtual void setWindowId(void* a);                              //设置窗口ID

    virtual void setParentId(void* a);                              //设置父ID

    virtual int* getPosition();                                     //获取图像位置

    virtual void setPosition(int x,int y);                          //设置图像位置

    virtual void setPosition(int a[2]);                             //设置图像位置

    virtual int* getSize();                                         //获取图像尺寸

    virtual void setSize(int width,int height);                     //设置图像尺寸

    virtual void setSize(int a[2]);                                 //设置图像尺寸

    virtual void setRenderWindow(vtkRenderWindow* arg);             //设置渲染窗口

    virtual void setRenderer(vtkRenderer* arg);                     //设置渲染器

    vtkRenderWindow* getRenderWindow();                             //获取渲染窗口

    vtkRenderer* getRenderer();                                     //获取渲染器

    vtkImageActor* getImageActor();                                 //获取Actor

    vtkImageMapToWindowLevelColors* getWindowLevel();               //获取图像信息

    vtkInteractorStyleImage* getInteratorStyle();                   //获取交互器

    virtual void setupInteractor(vtkRenderWindowInteractor*arg);    //设置交互器

    virtual void setOffScreenRendering(vtkTypeBool i);              //设置离屏渲染开关

    virtual vtkTypeBool getOffScreenRendering();                    //获取离屏渲染开关

    virtual void offScreenRenderingOn();                            //打开离屏渲染

    virtual void offScreenRenderingOff();                           //关闭离屏渲染

protected:

    ImagePipeLine();                                                //构造

    ~ImagePipeLine() override;                                      //析构

    virtual void updateOrientation();                               //设置相机位置

    vtkAlgorithm* getInputAlgorithm();                              //获取vtkAlgorithm

    vtkInformation* getInputInformation();                          //获取vtkInformation

    virtual void installPipeline();                                 //安装流水线

    virtual void unInstallPipeline();                               //卸载流水线


protected:

    vtkImageMapToWindowLevelColors* WindowLevel;
    vtkRenderWindow* RenderWindow;                                  //渲染窗口
    vtkRenderer* Renderer;                                          //渲染器
    vtkImageActor* ImageActor;                                      //ImageActor
    vtkRenderWindowInteractor* Interactor;                          //交互器
    vtkInteractorStyleImage* InteractorStyle;                       //交互样式
    int SliceOrientation;                                           //切片方向
    int FirstRender;                                                //第一次渲染标志
    int Slice;                                                      //当前切片

private:
    ImagePipeLine(const ImagePipeLine&) = delete;
    void operator=(const ImagePipeLine&) = delete;

};

#endif // IMAGEPIPELINE_H
