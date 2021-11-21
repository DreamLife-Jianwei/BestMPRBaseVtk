#ifndef BPPMPRWIDGET_H
#define BPPMPRWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include <QScopedPointer>


#include <QVTKInteractor.h>
#include <vtkGUISupportQtModule.h>
#include <vtkNew.h>
#include <vtkSmartPointer.h>


class QVTKInteractor;
class QVTKInteractorAdapter;
class QVTKRenderWindowAdapter;
class vtkGenericOpenGLRenderWindow;

class vtkImageData;
class vtkAlgorithmOutput;

class BPPMPRWidget : public QOpenGLWidget
{
    Q_OBJECT
    typedef QOpenGLWidget Superclass;


public:
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
     * @brief render
     * 渲染图像
     */
    void render();
    /**
     * @brief setInputData
     * @param in
     * 设置输入数据
     */
    void setInputData(vtkImageData* in);
    /**
     * @brief setInputData
     * @param in
     * 设置输入数据
     */
    void SetInputConnection(vtkAlgorithmOutput* input);
    /**
     * @brief getInput
     * @return
     * 获取出入数据
     */
    vtkImageData* getInput();

    /**
     * 切片方向
     */
    enum
    {
      SLICE_ORIENTATION_YZ = 0,
      SLICE_ORIENTATION_XZ = 1,
      SLICE_ORIENTATION_XY = 2
    };
    void setSliceOrientation(int orientation);

    void SetSliceOrientationToXY();

    void SetSliceOrientationToYZ();

    void SetSliceOrientationToXZ();
    /**
     * @brief getSliceOrientation
     * @return
     * 获取切片方向
     */
    int getSliceOrientation();
    /**
     * @brief setSlice
     * @param s
     * 设置当前显示层数
     */
    void setSlice(int s);
    /**
     * @brief getSlice
     * @return
     * 获取当前显示层数
     */
    int getSlice();
    /**
     * @brief UpdateDisplayExtent
     * 更新显示切片
     */
    void UpdateDisplayExtent();



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
};

#endif // BPPMPRWIDGET_H
