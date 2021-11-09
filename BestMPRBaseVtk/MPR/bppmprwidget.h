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
     * @brief VTK_LEGACY
     * @param SetRenderWindow
     */
    VTK_LEGACY(void SetRenderWindow(vtkGenericOpenGLRenderWindow* win));
    /**
     * @brief VTK_LEGACY
     * @param SetRenderWindow
     */
    VTK_LEGACY(void SetRenderWindow(vtkRenderWindow* win));
    /**
     * @brief VTK_LEGACY
     * @param GetRenderWindow
     */
    VTK_LEGACY(vtkRenderWindow* GetRenderWindow());
    /**
     * @brief VTK_LEGACY
     * @param GetInteractor
     */
    VTK_LEGACY(QVTKInteractor* GetInteractor());
    /**
     * @brief VTK_LEGACY
     * @param GetInteractorAdapter
     */
    VTK_LEGACY(QVTKInteractorAdapter* GetInteractorAdapter());
    /**
     * @brief VTK_LEGACY
     * @param setQVTKCursor
     */
    VTK_LEGACY(void setQVTKCursor(const QCursor& cursor));
    /**
     * @brief VTK_LEGACY
     * @param setDefaultQVTKCursor
     */
    VTK_LEGACY(void setDefaultQVTKCursor(const QCursor& cursor));

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

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> RenderWindow;

    QScopedPointer<QVTKRenderWindowAdapter> RenderWindowAdapter;

private:
    Q_DISABLE_COPY(BPPMPRWidget);

    bool EnableHiDPI;
    int UnscaledDPI;
    QCursor DefaultCursor;
};

#endif // BPPMPRWIDGET_H
