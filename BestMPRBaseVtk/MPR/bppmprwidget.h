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
    BPPMPRWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    BPPMPRWidget(vtkGenericOpenGLRenderWindow* window, QWidget* parent = nullptr,Qt::WindowFlags f = Qt::WindowFlags());

    ~BPPMPRWidget() override;


    /**
     * Set a render window to use. It a render window was already set, it will be
     * finalized and all of its OpenGL resource released. If the \c win is
     * non-null and it has no interactor set, then a QVTKInteractor instance will
     * be created as set on the render window as the interactor.
     */

    void setRenderWindow(vtkGenericOpenGLRenderWindow* win);

    void setRenderWindow(vtkRenderWindow* win);

    vtkRenderWindow* renderWindow() const;

    QVTKInteractor* interactor() const;

    static QSurfaceFormat defaultFormat(bool stereo_capable = false);

    void setEnableHiDPI(bool enable);

    bool enableHiDPI() const;

    void setUnscaledDPI(int dpi);

    int unscaledDPI() const;

    void setDefaultCursor(const QCursor& cursor);

    const QCursor& defaultCursor() const;

    VTK_LEGACY(void SetRenderWindow(vtkGenericOpenGLRenderWindow* win));

    VTK_LEGACY(void SetRenderWindow(vtkRenderWindow* win));

    VTK_LEGACY(vtkRenderWindow* GetRenderWindow());

    VTK_LEGACY(QVTKInteractor* GetInteractor());

    VTK_LEGACY(QVTKInteractorAdapter* GetInteractorAdapter());

    VTK_LEGACY(void setQVTKCursor(const QCursor& cursor));

    VTK_LEGACY(void setDefaultQVTKCursor(const QCursor& cursor));

protected slots:

    virtual void cleanupContext();

    void updateSize();
protected:
  bool event(QEvent* evt) override;

  void initializeGL() override;

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
