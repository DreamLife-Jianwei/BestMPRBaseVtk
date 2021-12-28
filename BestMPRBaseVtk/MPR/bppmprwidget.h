#ifndef BPPMPRWIDGET_H
#define BPPMPRWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include <QScopedPointer>
#include <QMouseEvent>

#include <QVTKInteractor.h>
#include <vtkGUISupportQtModule.h>
#include <vtkNew.h>
#include <vtkSmartPointer.h>

#include "imagepipeline.h"


class QVTKInteractor;
class QVTKInteractorAdapter;
class QVTKRenderWindowAdapter;
class vtkGenericOpenGLRenderWindow;


//https://www.cnblogs.com/biaohuang/p/14287854.html
//https://blog.csdn.net/liushao1031177/article/details/118946205


class BPPMPRWidget : public QOpenGLWidget
{
    Q_OBJECT
    typedef QOpenGLWidget Superclass;

public:                                                            /******公开接口******/

    BPPMPRWidget(QWidget* parent = nullptr,
                 Qt::WindowFlags f = Qt::WindowFlags());                //构造函数

    BPPMPRWidget(vtkGenericOpenGLRenderWindow* window,
                 QWidget* parent = nullptr,
                 Qt::WindowFlags f = Qt::WindowFlags());                //构造函数

    ~BPPMPRWidget() override;                                           //析构函数

    void setRenderWindow(vtkGenericOpenGLRenderWindow* win);            //设置渲染窗口

    void setRenderWindow(vtkRenderWindow* win);                         //设置渲染窗口

    vtkRenderWindow* renderWindow() const;                              //返回渲染窗口

    QVTKInteractor* interactor() const;                                 //返回交互器

    static QSurfaceFormat defaultFormat(bool stereo_capable = false);   //返回QSurfaceFormat

    void setEnableHiDPI(bool enable);                                   //启用或禁用HiDPI显示支持，当启用时，这将启用DPI伸缩，‘vtkWindow::SetDPI’将在每次小部件调整大小时使用按设备像素比例缩放的DPI值来调用，未缩放的DPI值可以使用‘setUnscaledDPI’来指定

    bool enableHiDPI() const;                                           //返回HiDPI显示支状态

    void setUnscaledDPI(int dpi = 72);                                  //设置、获取未缩放的DPI值，默认为72 也是vtkWindow默认的值

    int unscaledDPI() const;                                            //返回当前DPI

    void setDefaultCursor(const QCursor& cursor);                       //这是默认光标

    const QCursor& defaultCursor() const;                               //返回默认光标

    void setInputData(vtkImageData* data);                              //设置输入数据

    void setInputConnection(vtkAlgorithmOutput* input);                 //设置输入数据

    void render();                                                      //开始渲染

    enum
    {
        //切片方向
        SLICE_ORIENTATION_YZ = 0,
        SLICE_ORIENTATION_XZ = 1,
        SLICE_ORIENTATION_XY = 2
    };

    int getSliceOrientation();                                          //获取切片方向

    void setSliceOrientation(int orientation);                          //设置切片方向

    void setSliceOrientationToXY();                                     //设置切片方向

    void setSliceOrientationToYZ();                                     //设置切片方向

    void setSliceOrientationToXZ();                                     //设置切片方向

    virtual int getSlice();                                             //获取图像序列

    virtual void setSlice(int slice);                                   //设置图像序列

    void updateDisplayExtent();                                         //更新显示范围

    int getSliceMin();                                                  //获取最小切片
    /**
     * @brief getSliceMax
     * @return
     * 获取最大切片
     */
    int getSliceMax();                                                  //获取最大切片

    void getSliceRange(int range[2]);                                   //获取切片范围

    void getSliceRange(int& min, int& max);                             //获取切片范围

    int* getSliceRange();                                               //获取切片范围
    /**
     * @brief getColorWindow
     * @return
     * 获取窗宽
     */
    double getColorWindow();                                            //获取窗宽

    double getColorLevel();                                             //获取窗位

    void setColorWindow(double s);                                      //设置窗宽

    void setColorLevel(double s);                                       //设置窗位

    void setDisplayId(void* a);                                         //设置显示ID

    void setWindowId(void* a);                                          //设置窗口ID

    void setParentId(void* a);                                          //设置父ID

    int* getPosition();                                                 //获取位置

    void setPosition(int x,int y);                                      //设置位置

    void setPosition(int a[2]);                                         //设置位置

    int* getSize();                                                     //获取尺寸

    void setSize(int width,int height);                                 //设置尺寸

    void setSize(int a[2]);                                             //设置尺寸

    void setRenderer(vtkRenderer* arg);                                 //设置渲染器

    vtkRenderWindow* getRenderWindow();                                 //获取渲染窗口

    vtkRenderer* getRenderer();                                         //获取渲染器

    vtkImageActor* getImageActor();                                     //获取ImageActor

    vtkImageMapToWindowLevelColors* getWindowLevel();                   //获取颜色映射表

    vtkInteractorStyleImage* getInteratorStyle();                       //获取交互器

    void setupInteractor(vtkRenderWindowInteractor*arg);                //设置交互器

    void setOffScreenRendering(vtkTypeBool i);                          //设置离屏渲染开关

    vtkTypeBool getOffScreenRendering();                                //获取离屏渲染状态

    void offScreenRenderingOn();                                        //打开离屏渲染

    void offScreenRenderingOff();                                       //关闭离屏渲染

    void update();                                                      //界面更新函数

    void mousePressEvent(QMouseEvent* event) override;                  //鼠标按下事件

    void mouseMoveEvent(QMouseEvent* event) override;                   //鼠标移动事件

    void mouseReleaseEvent(QMouseEvent* event) override;                //鼠标松开事件

    void mouseDoubleClickEvent(QMouseEvent* event) override;            //鼠标双击事件

    void wheelEvent(QWheelEvent* event) override;                       //鼠标滚轮事件

    void keyPressEvent(QKeyEvent* event) override;                      //键盘按键按下事件

    void keyReleaseEvent(QKeyEvent* event) override;                    //键盘按键松开事件

    void enterEvent(QEvent* event) override;                            //进入事件

    void leaveEvent(QEvent* event) override;                            //离开事件

public:                                                            /******公开属性，目前仅为公开变量，在实际插件中，将对应为属性******/

    double colorWindow = 0.0;                                           //窗宽
    double colorLevel = 0.0;                                            //窗位
    int slice = 0;                                                      //当前切片
    int minSLice = 0;                                                   //最小切片
    int maxSlice = 0;                                                   //最大切片

signals:

    void onSliceChanged(int slice);                                     //Slice改变信号

    void onColorWindowChanged(double colorWindow);                      //窗宽改变信号

    void onColorLevelChanged(double colorLevel);                        //窗位改变信号

    void onPositonChanged(int x,int y);                                 //鼠标位置改变信号
protected slots:

    virtual void cleanupContext();                                      //清除上下文

    void updateSize();                                                  //更新尺寸

protected:

    bool event(QEvent* evt) override;                                   //event事件

    void initializeGL() override;                                       //初始化OpenGL

    void paintGL() override;                                            //OpenGL 绘制


protected:

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> RenderWindow;         //渲染窗口
    QScopedPointer<QVTKRenderWindowAdapter> RenderWindowAdapter;        //窗口管理器
    friend class myVtkInteractorStyleImage;                             //把交互类声明为友元类，为了访问私有信号触发接口

private:
    void emitPositionChangedSignal(int* temp);

    void emitSliceChangedSignal(int temp);


private:

    Q_DISABLE_COPY(BPPMPRWidget);                                       //禁用拷贝构造
    bool EnableHiDPI;
    int UnscaledDPI;
    QCursor DefaultCursor;
    ImagePipeLine* m_PipeLine = nullptr;
};

#endif // BPPMPRWIDGET_H
