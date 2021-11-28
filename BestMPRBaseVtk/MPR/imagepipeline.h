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
    /**
     * @brief getWindowName
     * @return
     * 获取窗口名称
     */
    virtual const char* getWindowName();
    /**
     * @brief Render
     * 开始渲染图像
     */
    virtual void render();
    /**
     * @brief getInput
     * @return
     * 获取输入数据
     */
    virtual vtkImageData* getInput();
    /**
     * @brief setInputData
     * @param in
     * 设置输入数据
     */
    virtual void setInputData(vtkImageData* in);
    /**
     * @brief setInputConnection
     * @param input
     * 设置输入数据
     */
    virtual void setInputConnection(vtkAlgorithmOutput* input);
    /**
     * 切片方向
     */
    enum
     {
       SLICE_ORIENTATION_YZ = 0,
       SLICE_ORIENTATION_XZ = 1,
       SLICE_ORIENTATION_XY = 2
     };

    int getSliceOrientation();
    /**
     * @brief ImagePipeLine::setSliceOrientation
     * @param orientation
     * 设置切片方向
     */
    virtual void setSliceOrientation(int orientation);
    /**
     * @brief setSliceOrientationToXY
     * 设置切片方向
     */
    virtual void setSliceOrientationToXY();
    /**
     * @brief setSliceOrientationToXY
     * 设置切片方向
     */
    virtual void setSliceOrientationToYZ();
    /**
     * @brief setSliceOrientationToXY
     * 设置切片方向
     */
    virtual void setSliceOrientationToXZ();
    /**
     * @brief updateDisplayExtent
     * 更新显示
     */
    virtual void updateDisplayExtent();
    /**
     * @brief getSliceMin
     * @return
     * 获取最小切片
     */
    virtual int getSliceMin();
    /**
     * @brief getSliceMax
     * @return
     * 获取最大切片
     */
    virtual int getSliceMax();
    /**
     * @brief getSliceRange
     * @param range
     * 获取切片范围
     */
    virtual void getSliceRange(int range[2]);
    /**
     * @brief getSliceRange
     * @param min
     * @param max
     * 获取切片范围
     */
    virtual void getSliceRange(int& min, int& max);
    /**
     * @brief getSliceRange
     * @return
     * 获取切片范围
     */
    virtual int* getSliceRange();
    /**
     * @brief getColorWindow
     * @return
     * 获取窗宽
     */
    virtual double getColorWindow();
    /**
     * @brief getColorLevel
     * @return
     * 获取窗位
     */
    virtual double getColorLevel();
    /**
     * @brief setColorWindow
     * @param s
     * 设置窗宽
     */
    virtual void setColorWindow(double s);
    /**
     * @brief setColorLevel
     * @param s
     * 设置窗位
     */
    virtual void setColorLevel(double s);

    /**
     * These are here when using a Tk window.
     */
    virtual void setDisolayId(void* a);

    virtual void setWindowId(void* a);

    virtual void setParentId(void* a);
    /**
     * @brief getPosition
     * @return
     * 获取图像位置
     */
    virtual int* getPosition();

    virtual void setPosition(int x,int y);

    virtual void setPosition(int a[2]);

    virtual int* getSize();

    virtual void setSize(int width,int height);

    virtual void setSize(int a[2]);


    /**
     * @brief ImagePipeLine::setRenderWindow
     * @param arg
     * 设置渲染窗口
     */
    virtual void setRenderWindow(vtkRenderWindow* arg);
    /**
     * @brief ImagePipeLine::setRenderer
     * @param arg
     * 设置渲染器
     */
    virtual void setRenderer(vtkRenderer* arg);
    /**
     * @brief getRenderWindow
     * @return
     * 获取渲染窗口
     */
    vtkRenderWindow* getRenderWindow();
    /**
     * @brief getRenderer
     * @return
     * 获取渲染器
     */
    vtkRenderer* getRenderer();
    /**
     * @brief getImageActor
     * @return
     * 获取演员
     */
    vtkImageActor* getImageActor();
    /**
     * @brief getWindowLevel
     * @return
     * 获取图像信息
     */
    vtkImageMapToWindowLevelColors* getWindowLevel();
    /**
     * @brief getInteratorStyle
     * @return
     * 获取交互器
     */
    vtkInteractorStyleImage* getInteratorStyle();
    /**
     * @brief setupInteractor
     * @param arg
     * 设置交互器
     */
    virtual void setupInteractor(vtkRenderWindowInteractor*arg);

    virtual void setOffScreenRendering(vtkTypeBool i);

    virtual vtkTypeBool getOffScreenRendering();

    virtual void offScreenRenderingOn();

    virtual void offScreenRenderingOff();

protected:
    ImagePipeLine();
    ~ImagePipeLine() override;
    /**
     * @brief updateOrientation
     * 设置相机位置
     */
    virtual void updateOrientation();
    /**
     * @brief getInputAlgorithm
     * @return
     */
    vtkAlgorithm* getInputAlgorithm();
    /**
     * @brief getInputInformation
     * @return
     */
    vtkInformation* getInputInformation();
    /**
     * @brief installPipeline
     * 安装流水线
     */
    virtual void installPipeline();
    /**
     * @brief unInstallPipeline
     * 卸载流水线
     */
    virtual void unInstallPipeline();
protected:
    vtkImageMapToWindowLevelColors* WindowLevel;
    vtkRenderWindow* RenderWindow;
    vtkRenderer* Renderer;
    vtkImageActor* ImageActor;
    vtkRenderWindowInteractor* Interactor;
    vtkInteractorStyleImage* InteractorStyle;
    int SliceOrientation;
    int FirstRender;
    int Slice;
    friend class ImagePipeLineCallback;

signals:

private:
    ImagePipeLine(const ImagePipeLine&) = delete;
    void operator=(const ImagePipeLine&) = delete;

};

#endif // IMAGEPIPELINE_H
