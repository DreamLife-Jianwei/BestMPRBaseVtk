#include "bppmprwidget.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_2_Core>
#include <QOpenGLTexture>
#include <QPointer>
#include <QScopedValueRollback>
#include <QtDebug>

#include "QVTKInteractor.h"
#include "QVTKInteractorAdapter.h"
#include "QVTKRenderWindowAdapter.h"
#include "vtkCommand.h"
#include "vtkGenericOpenGLRenderWindow.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkNew.h"
#include "vtkObjectFactory.h"
#include "vtkOpenGLState.h"

BPPMPRWidget::BPPMPRWidget(QWidget *parent, Qt::WindowFlags f) : BPPMPRWidget(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New().GetPointer(),parent,f)
{

}

BPPMPRWidget::BPPMPRWidget(vtkGenericOpenGLRenderWindow *window, QWidget *parent, Qt::WindowFlags f) : Superclass(parent,f),RenderWindow(nullptr),RenderWindowAdapter(nullptr),EnableHiDPI(true),UnscaledDPI(72),DefaultCursor(QCursor(Qt::ArrowCursor))
{

    //默认设置为强焦点
    this->setFocusPolicy(Qt::StrongFocus);                                      //焦点策略，即小部件可以通过Tab键和单击接受焦点，在MacOS上，这也表明当处于"文档、列表焦点模式"时，小部件接受选项卡焦点
    this->setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);                    //缓存区刷新策略，不使用部分绘制
    this->setMouseTracking(true);                                               //实时监听鼠标事件
    //使用本地updateSize替换原来的resize
    this->connect(this,&BPPMPRWidget::resized,this,&BPPMPRWidget::updateSize);  //这个和直接调用应该没有啥区别
    this->setRenderWindow(window);                                              //设置渲染窗口
    //启用Qt手势支持
    this->grabGesture(Qt::PinchGesture);
    this->grabGesture(Qt::PanGesture);
    this->grabGesture(Qt::TapGesture);
    this->grabGesture(Qt::TapAndHoldGesture);
    this->grabGesture(Qt::SwipeGesture);
}

BPPMPRWidget::~BPPMPRWidget()
{
    this->makeCurrent();
    this->cleanupContext();
}

void BPPMPRWidget::setRenderWindow(vtkGenericOpenGLRenderWindow *win)
{
    if(this->RenderWindow == win)               //判断当前窗口是不是传进来的，是就返回不是继续
    {
        return;
    }

    if(this->RenderWindowAdapter)               // 这将释放所有与旧窗口相关的OpenGL资源
    {
        this->makeCurrent();
        this->RenderWindowAdapter.reset(nullptr);
    }

    this->RenderWindow = win;
    if(this->RenderWindow)
    {
        this->RenderWindow->SetReadyForRendering(false);
        //如果没有提供交互器，我们默认将创建一个
        if(!this->RenderWindow->GetInteractor())
        {
            vtkNew<QVTKInteractor> iren;                //创建一个默认交互器
            this->RenderWindow->SetInteractor(iren);    //为RenderWindow添加交互器
            iren->Initialize();                         //交互器初始化
            //设置交互器默认样式
            vtkNew<vtkInteractorStyleTrackballCamera> style;
            iren->SetInteractorStyle(style);
        }
        if(this->isValid())
        {
            this->makeCurrent();
            this->initializeGL();
            this->updateSize();
        }
    }
}

void BPPMPRWidget::setRenderWindow(vtkRenderWindow *win)
{
    //做类型转换
    auto gwin = vtkGenericOpenGLRenderWindow::SafeDownCast(win);
    if(win != nullptr && gwin == nullptr)                                       //转换失败，则提示类型不支持
    {
        qDebug() << "QVTKOpenGLNativeWidget requires a `vtkGenericOpenGLRenderWindow`. `"
                 << win->GetClassName() << "` is not supported.";
    }
    this->setRenderWindow(gwin);                //调用另一个setRenderWindow
}

vtkRenderWindow *BPPMPRWidget::renderWindow() const
{
    return this->RenderWindow;                          //返回窗口指针
}

QVTKInteractor *BPPMPRWidget::interactor() const
{
    return this->RenderWindow ? QVTKInteractor::SafeDownCast(this->RenderWindow->GetInteractor()) : nullptr;            //返回窗口交互器
}

QSurfaceFormat BPPMPRWidget::defaultFormat(bool stereo_capable)
{
    return QVTKRenderWindowAdapter::defaultFormat(stereo_capable);              //返回默认QSurfaceFormat
}
/**
 * @brief BPPMPRWidget::setEnableHiDPI
 * @param enable
 */
void BPPMPRWidget::setEnableHiDPI(bool enable)
{
    this->EnableHiDPI = enable;
    if(this->RenderWindowAdapter)
    {
        this->RenderWindowAdapter->setEnableHiDPI(enable);
    }
}

bool BPPMPRWidget::enableHiDPI() const
{
    return this->EnableHiDPI;
}

void BPPMPRWidget::setUnscaledDPI(int dpi)
{
    this->UnscaledDPI = dpi;
    if(this->RenderWindowAdapter)
    {
        this->RenderWindowAdapter->setUnscaledDPI(dpi);
    }
}

int BPPMPRWidget::unscaledDPI() const
{
    return this->UnscaledDPI;
}

void BPPMPRWidget::setDefaultCursor(const QCursor &cursor)
{
    this->DefaultCursor = cursor;
    if(this->RenderWindowAdapter)
    {
        this->RenderWindowAdapter->setDefaultCursor(cursor);
    }
}

const QCursor &BPPMPRWidget::defaultCursor() const
{
    return this->DefaultCursor;
}

void BPPMPRWidget::cleanupContext()
{
    this->RenderWindowAdapter.reset(nullptr);
}

void BPPMPRWidget::updateSize()
{
    if(this->RenderWindowAdapter)
    {
        this->RenderWindowAdapter->resize(this->width(),this->height());
    }
}

bool BPPMPRWidget::event(QEvent *evt)
{

    if(this->RenderWindowAdapter)
    {
        this->RenderWindowAdapter->handleEvent(evt);
    }


    return this->Superclass::event(evt);
}

void BPPMPRWidget::initializeGL()
{
    this->Superclass::initializeGL();
    if(this->RenderWindow)
    {
        Q_ASSERT(this->RenderWindowAdapter.data() == nullptr);              //测试代码

        this->RenderWindowAdapter.reset(new QVTKRenderWindowAdapter(this->context(),this->RenderWindow,this));  //重置
        this->RenderWindowAdapter->setDefaultCursor(this->defaultCursor());         //设置默认光标
        this->RenderWindowAdapter->setEnableHiDPI(this->EnableHiDPI);               //设置HiDPI
        this->RenderWindowAdapter->setUnscaledDPI(this->UnscaledDPI);               //设置默认DPI
    }

    this->connect(this->context(),&QOpenGLContext::aboutToBeDestroyed,this,&BPPMPRWidget::cleanupContext,static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::DirectConnection)); //连接信号槽

}

void BPPMPRWidget::paintGL()
{
    this->Superclass::paintGL();
    if(this->RenderWindow)
    {
        Q_ASSERT(this->RenderWindowAdapter);
        this->RenderWindowAdapter->paint();

        this->makeCurrent();                    //在大多数情况下，没有必要调用这个函数，因为在调用paintGL()之前会自动调用它。

        QOpenGLFunctions_3_2_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_2_Core>();

        if(f)
        {
            const QSize deviceSize = this->size() * this->devicePixelRatioF();
            this->RenderWindowAdapter->blit(this->defaultFramebufferObject(),GL_COLOR_ATTACHMENT0,QRect(QPoint(0,0),deviceSize));
        }
    }
    else
    {
        QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
        f->glClearColor(1.0f,1.0f,1.0f,1.0f);
        f->glClear(GL_COLOR_BUFFER_BIT);
    }
}

#if !defined(VTK_LEGACY_REMOVE)
void BPPMPRWidget::SetRenderWindow(vtkRenderWindow* win)
{
  VTK_LEGACY_REPLACED_BODY(
    QVTKOpenGLNativeWidget::SetRenderWindow, "VTK 9.0", QVTKOpenGLNativeWidget::setRenderWindow);
  vtkGenericOpenGLRenderWindow* gwin = vtkGenericOpenGLRenderWindow::SafeDownCast(win);
  if (gwin == nullptr && win != nullptr)
  {
    qDebug() << "QVTKOpenGLNativeWidget requires a `vtkGenericOpenGLRenderWindow`. `"
             << win->GetClassName() << "` is not supported.";
  }
  this->setRenderWindow(gwin);
}
#endif

//-----------------------------------------------------------------------------
#if !defined(VTK_LEGACY_REMOVE)
void BPPMPRWidget::SetRenderWindow(vtkGenericOpenGLRenderWindow* win)
{
  VTK_LEGACY_REPLACED_BODY(
    QVTKOpenGLNativeWidget::SetRenderWindow, "VTK 9.0", QVTKOpenGLNativeWidget::setRenderWindow);
  this->setRenderWindow(win);
}
#endif

//-----------------------------------------------------------------------------
#if !defined(VTK_LEGACY_REMOVE)
vtkRenderWindow* BPPMPRWidget::GetRenderWindow()
{
  VTK_LEGACY_REPLACED_BODY(
    QVTKOpenGLNativeWidget::GetRenderWindow, "VTK 9.0", QVTKOpenGLNativeWidget::renderWindow);
  return this->renderWindow();
}
#endif

//-----------------------------------------------------------------------------
#if !defined(VTK_LEGACY_REMOVE)
QVTKInteractorAdapter* BPPMPRWidget::GetInteractorAdapter()
{
  VTK_LEGACY_BODY(QVTKOpenGLNativeWidget::GetInteractorAdapter, "VTK 9.0");
  return nullptr;
}
#endif

//-----------------------------------------------------------------------------
#if !defined(VTK_LEGACY_REMOVE)
QVTKInteractor* BPPMPRWidget::GetInteractor()
{
  VTK_LEGACY_REPLACED_BODY(
    QVTKOpenGLNativeWidget::GetInteractor, "VTK 9.0", QVTKOpenGLNativeWidget::interactor);
  return this->interactor();
}
#endif

//-----------------------------------------------------------------------------
#if !defined(VTK_LEGACY_REMOVE)
void BPPMPRWidget::setQVTKCursor(const QCursor& cursor)
{
  VTK_LEGACY_REPLACED_BODY(
    QVTKOpenGLNativeWidget::setQVTKCursor, "VTK 9.0", QVTKOpenGLNativeWidget::setCursor);
  this->setCursor(cursor);
}
#endif

//-----------------------------------------------------------------------------
#if !defined(VTK_LEGACY_REMOVE)
void BPPMPRWidget::setDefaultQVTKCursor(const QCursor& cursor)
{
  VTK_LEGACY_REPLACED_BODY(QVTKOpenGLNativeWidget::setDefaultQVTKCursor, "VTK 9.0",
    QVTKOpenGLNativeWidget::setDefaultCursor);
  this->setDefaultCursor(cursor);
}
#endif
