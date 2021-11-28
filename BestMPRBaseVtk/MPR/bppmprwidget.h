#ifndef BPPMPRWIDGET_H
#define BPPMPRWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include <QScopedPointer>


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

    void updateDisplayExtent();

    int getSliceMin();

    int getSliceMax();

    void getSliceRange(int range[2]);

    void getSliceRange(int& min, int& max);

    int* getSliceRange();

    double getColorWindow();

    double getColorLevel();

    void setColorWindow(double s);

    void setColorLevel(double s);

    void setDisolayId(void* a);

    void setWindowId(void* a);

    void setParentId(void* a);

    int* getPosition();

    void setPosition(int x,int y);

    void setPosition(int a[2]);

    int* getSize();

    void setSize(int width,int height);

    void setSize(int a[2]);


    void setRenderer(vtkRenderer* arg);

    vtkRenderWindow* getRenderWindow();

    vtkRenderer* getRenderer();

    vtkImageActor* getImageActor();

    vtkImageMapToWindowLevelColors* getWindowLevel();

    vtkInteractorStyleImage* getInteratorStyle();

    void setupInteractor(vtkRenderWindowInteractor*arg);

    void setOffScreenRendering(vtkTypeBool i);

    vtkTypeBool getOffScreenRendering();

    void offScreenRenderingOn();

    void offScreenRenderingOff();


public:                                                         //公开属性


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
