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

class BPPMPRWidget : public QOpenGLWidget
{
    Q_OBJECT
    typedef QOpenGLWidget Superclass;
public:                                                             //公开接口
    /**
     * @brief BPPMPRWidget
     * @param parent
     * @param f
     * 构造函数
     */
    BPPMPRWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    /**
     * @brief BPPMPRWidget
     * @param window
     * @param parent
     * @param f
     * 构造函数
     */
    BPPMPRWidget(vtkGenericOpenGLRenderWindow* window, QWidget* parent = nullptr,Qt::WindowFlags f = Qt::WindowFlags());
    /**
     * 析构函数
     *
     */
    ~BPPMPRWidget() override;
    /**
     * @brief setRenderWindow
     * @param win
     */
    void setRenderWindow(vtkGenericOpenGLRenderWindow* win);
    /**
     * @brief setRenderWindow
     * @param win
     */
    void setRenderWindow(vtkRenderWindow* win);
    /**
     * @brief renderWindow
     * @return
     */
    vtkRenderWindow* renderWindow() const;
    /**
     * @brief interactor
     * @return
     */
    QVTKInteractor* interactor() const;
    /**
     * @brief defaultFormat
     * @param stereo_capable
     * @return
     */
    static QSurfaceFormat defaultFormat(bool stereo_capable = false);
    /**
     * @brief setEnableHiDPI
     * @param enable
     * 启用或禁用HiDPI显示支持，当启用时，这将启用DPI伸缩，‘vtkWindow::SetDPI’将在每次小部件调整大小时使用按设备像素比例缩放的DPI值来调用，未缩放的DPI值可以使用‘setUnscaledDPI’来指定
     */
    void setEnableHiDPI(bool enable);
    /**
     * @brief enableHiDPI
     * @return
     */
    bool enableHiDPI() const;
    /**
     * @brief setUnscaledDPI
     * @param dpi
     * 设置、获取未缩放的DPI值，默认为72 也是vtkWindow默认的值
     */
    void setUnscaledDPI(int dpi = 72);
    /**
     * @brief unscaledDPI
     * @return
     * 返回当前DPI
     */
    int unscaledDPI() const;
    /**
     * @brief setDefaultCursor
     * @param cursor
     * 设置光标
     */
    void setDefaultCursor(const QCursor& cursor);
    /**
     * @brief defaultCursor
     * @return
     * 获取光标
     */
    const QCursor& defaultCursor() const;
    /**
     * @brief setInputData
     * @param data 输入数据
     * 设置输入数据
     */
    void setInputData(vtkImageData* data);
    /**
     * @brief setInputConnection
     * @param input
     * 设置输入数据
     */
    void setInputConnection(vtkAlgorithmOutput* input);
    /**
     * @brief render
     * 开始渲染
     */
    void render();

    /**
     * 切片方向
     */
    enum
    {
        SLICE_ORIENTATION_YZ = 0,
        SLICE_ORIENTATION_XZ = 1,
        SLICE_ORIENTATION_XY = 2
    };
    /**
     * @brief getSliceOrientation
     * @return
     * 获取切片方向
     */
    int getSliceOrientation();
    /**
     * @brief ImagePipeLine::setSliceOrientation
     * @param orientation
     * 设置切片方向
     */
    void setSliceOrientation(int orientation);
    /**
     * @brief setSliceOrientationToXY
     * 设置切片方向
     */
    void setSliceOrientationToXY();
    /**
     * @brief setSliceOrientationToXY
     * 设置切片方向
     */
    void setSliceOrientationToYZ();
    /**
     * @brief setSliceOrientationToXY
     * 设置切片方向
     */
    void setSliceOrientationToXZ();
    /**
     * @brief ImagePipeLine::getSlice
     * @return
     * 获取图像序列
     */
    virtual int getSlice();
    /**
     * @brief ImagePipeLine::setSlice
     * @param s
     * 设置图像序列
     */
    virtual void setSlice(int slice);
    /**
     * @brief updateDisplayExtent
     * 更新显示范围
     */
    void updateDisplayExtent();
    /**
     * @brief getSliceMin
     * @return
     * 获取最小切片
     */
    int getSliceMin();
    /**
     * @brief getSliceMax
     * @return
     * 获取最大切片
     */
    int getSliceMax();
    /**
     * @brief getSliceRange
     * @param range
     * 获取切片范围
     */
    void getSliceRange(int range[2]);
    /**
     * @brief getSliceRange
     * @param min
     * @param max
     * 获取切片范围
     */
    void getSliceRange(int& min, int& max);
    /**
     * @brief getSliceRange
     * @return
     * 获取切片范围
     */
    int* getSliceRange();
    /**
     * @brief getColorWindow
     * @return
     * 获取窗宽
     */
    double getColorWindow();
    /**
     * @brief getColorLevel
     * @return
     * 获取窗位
     */
    double getColorLevel();
    /**
     * @brief setColorWindow
     * @param s
     * 设置窗宽
     */
    void setColorWindow(double s);
    /**
     * @brief setColorLevel
     * @param s
     * 设置窗位
     */
    void setColorLevel(double s);
    /**
     * @brief setDisplayId
     * @param a
     * 设置显示ID
     */
    void setDisplayId(void* a);
    /**
     * @brief setWindowId
     * @param a
     * 设置窗口ID
     */
    void setWindowId(void* a);
    /**
     * @brief setParentId
     * @param a
     * 设置父窗口ID
     */
    void setParentId(void* a);
    /**
     * @brief getPosition
     * @return
     * 获取位置
     */
    int* getPosition();
    /**
     * @brief setPosition
     * @param x
     * @param y
     * 设置位置
     */
    void setPosition(int x,int y);
    /**
     * @brief setPosition
     * @param a
     * 设置位置
     */
    void setPosition(int a[2]);
    /**
     * @brief getSize
     * @return
     * 获取尺寸
     */
    int* getSize();
    /**
     * @brief setSize
     * @param width
     * @param height
     * 设置尺寸
     */
    void setSize(int width,int height);
    /**
     * @brief setSize
     * @param a
     * 设置尺寸
     */
    void setSize(int a[2]);
    /**
     * @brief setRenderer
     * @param arg
     * 设置渲染器
     */
    void setRenderer(vtkRenderer* arg);
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
     * 获取ImageActor
     */
    vtkImageActor* getImageActor();
    /**
     * @brief getWindowLevel
     * @return
     * 获取窗位
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
    void setupInteractor(vtkRenderWindowInteractor*arg);
    /**
     * @brief setOffScreenRendering
     * @param i
     * 设置离屏渲染开关
     */
    void setOffScreenRendering(vtkTypeBool i);
    /**
     * @brief getOffScreenRendering
     * @return
     * 获取离屏渲染状态
     */
    vtkTypeBool getOffScreenRendering();
    /**
     * @brief offScreenRenderingOn
     * 打开离屏渲染
     */
    void offScreenRenderingOn();
    /**
     * @brief offScreenRenderingOff
     * 关闭离屏渲染
     */
    void offScreenRenderingOff();
    /**
     * @brief update
     * 界面更新函数
     */
    void update();
    /**
     * @brief mousePressEvent
     * @param event
     * 鼠标按下事件
     */
    void mousePressEvent(QMouseEvent* event) override;
    /**
     * @brief mouseMoveEvent
     * @param event
     * 鼠标移动事件
     */
    void mouseMoveEvent(QMouseEvent* event) override;
    /**
     * @brief mouseReleaseEvent
     * @param event
     * 鼠标松开事件
     */
    void mouseReleaseEvent(QMouseEvent* event) override;
    /**
     * @brief mouseDoubleClickEvent
     * @param event
     * 鼠标双击事件
     */
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    /**
     * @brief wheelEvent
     * @param event
     * 鼠标滚轮事件
     */
    void wheelEvent(QWheelEvent* event) override;



public:                                         //公开属性

    double colorWindow = 0.0;                   //窗宽
    double colorLevel = 0.0;                    //窗位

protected slots:
    /**
     * @brief cleanupContext
     */
    virtual void cleanupContext();
    /**
     * @brief updateSize
     */
    void updateSize();
protected:
    /**
     * @brief event
     * @param evt
     * @return
     */
    bool event(QEvent* evt) override;
    /**
     * @brief initializeGL
     */
    void initializeGL() override;
    /**
     * @brief paintGL
     */
    void paintGL() override;


protected:
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> RenderWindow;                 //渲染窗口
    QScopedPointer<QVTKRenderWindowAdapter> RenderWindowAdapter;                //窗口管理器



private:

    Q_DISABLE_COPY(BPPMPRWidget);           //禁用拷贝构造

    bool EnableHiDPI;
    int UnscaledDPI;
    QCursor DefaultCursor;

    ImagePipeLine* m_PipeLine = nullptr;
};

#endif // BPPMPRWIDGET_H
