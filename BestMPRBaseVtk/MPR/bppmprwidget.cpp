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




/**
 * @brief BPPMPRWidget::BPPMPRWidget
 * @param parent
 * @param f
 * 构造函数，调用另一个构造函数
 */
BPPMPRWidget::BPPMPRWidget(QWidget *parent, Qt::WindowFlags f) : BPPMPRWidget(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New().GetPointer(),parent,f)
{



}
/**
 * @brief BPPMPRWidget::BPPMPRWidget
 * @param window
 * @param parent
 * @param f
 * 最终的构造函数，完成控件焦点设置，
 */
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
/**
 * @brief BPPMPRWidget::~BPPMPRWidget
 * 析构函数
 */
BPPMPRWidget::~BPPMPRWidget()
{
    this->makeCurrent();
    this->cleanupContext();
}
/**
 * @brief BPPMPRWidget::setRenderWindow
 * @param win
 * 设置渲染窗口
 */
void BPPMPRWidget::setRenderWindow(vtkGenericOpenGLRenderWindow *win)
{
    if(this->RenderWindow == win)                               //判断当前窗口是不是传进来的，是就返回不是继续
    {
        return;
    }

    if(this->RenderWindowAdapter)                               // 这将释放所有与旧窗口相关的OpenGL资源
    {
        this->makeCurrent();                                    //为窗口绘制OpenGL内容做准备，将上下文设置为当前，并为该上下文绑定framebuffer
        this->RenderWindowAdapter.reset(nullptr);               //删除并重置指针
    }

    this->RenderWindow = win;                                   //赋新值
    if(this->RenderWindow)
    {
        this->RenderWindow->SetReadyForRendering(false);

        if(!this->RenderWindow->GetInteractor())                //如果没有提供交互器，我们默认将创建一个
        {
            vtkNew<QVTKInteractor> iren;                        //创建一个默认交互器
            this->RenderWindow->SetInteractor(iren);            //为RenderWindow添加交互器
            iren->Initialize();                                 //交互器初始化
            vtkNew<vtkInteractorStyleTrackballCamera> style;    //设置交互器默认样式
            iren->SetInteractorStyle(style);
        }
        if(this->isValid())
        {
            this->makeCurrent();                                //为窗口绘制OpenG内容做准备，将上下文设置为当前，并为该上下文绑定framebuffer paintGL会自动调用。
            this->initializeGL();                               //初始化Openg
            this->updateSize();                                 //更新窗口尺寸
        }
    }
}
/**
 * @brief BPPMPRWidget::setRenderWindow
 * @param win
 * 设置渲染窗口
 */
void BPPMPRWidget::setRenderWindow(vtkRenderWindow *win)
{
    auto gwin = vtkGenericOpenGLRenderWindow::SafeDownCast(win);                                                                                //做类型转换
    if(win != nullptr && gwin == nullptr)                                                                                                       //转换失败，则提示类型不支持
        qDebug() << "QVTKOpenGLNativeWidget requires a `vtkGenericOpenGLRenderWindow`. `" << win->GetClassName() << "` is not supported.";      //输出信息，后期得该到日志系统里面
    this->setRenderWindow(gwin);                                                                                                                //调用另一个setRenderWindow
}
/**
 * @brief BPPMPRWidget::renderWindow
 * @return
 * 返回窗口指针
 */
vtkRenderWindow *BPPMPRWidget::renderWindow() const
{
    return this->RenderWindow;                          //返回窗口指针
}
/**
 * @brief BPPMPRWidget::interactor
 * @return
 * 返回窗口交互器
 */
QVTKInteractor *BPPMPRWidget::interactor() const
{
    return this->RenderWindow ? QVTKInteractor::SafeDownCast(this->RenderWindow->GetInteractor()) : nullptr;            //返回窗口交互器
}
/**
 * @brief BPPMPRWidget::defaultFormat
 * @param stereo_capable
 * @return
 * 返回QSurfaceFormat
 */
QSurfaceFormat BPPMPRWidget::defaultFormat(bool stereo_capable)
{
    return QVTKRenderWindowAdapter::defaultFormat(stereo_capable);              //返回默认QSurfaceFormat
}
/**
 * @brief BPPMPRWidget::setEnableHiDPI
 * @param enable
 * 设置高DPI支持
 */
void BPPMPRWidget::setEnableHiDPI(bool enable)
{
    this->EnableHiDPI = enable;
    if(this->RenderWindowAdapter)
    {
        this->RenderWindowAdapter->setEnableHiDPI(enable);
    }
}
/**
 * @brief BPPMPRWidget::enableHiDPI
 * @return
 * 返回高DPI状态
 */
bool BPPMPRWidget::enableHiDPI() const
{
    return this->EnableHiDPI;
}
/**
 * @brief BPPMPRWidget::setUnscaledDPI
 * @param dpi
 * 设置默认DPI
 */
void BPPMPRWidget::setUnscaledDPI(int dpi)
{
    this->UnscaledDPI = dpi;
    if(this->RenderWindowAdapter)
    {
        this->RenderWindowAdapter->setUnscaledDPI(dpi);
    }
}
/**
 * @brief BPPMPRWidget::unscaledDPI
 * @return
 * 返回默认PDI
 */
int BPPMPRWidget::unscaledDPI() const
{
    return this->UnscaledDPI;
}
/**
 * @brief BPPMPRWidget::setDefaultCursor
 * @param cursor
 * 设置默认光标
 */
void BPPMPRWidget::setDefaultCursor(const QCursor &cursor)
{
    this->DefaultCursor = cursor;
    if(this->RenderWindowAdapter)
    {
        this->RenderWindowAdapter->setDefaultCursor(cursor);
    }
}
/**
 * @brief BPPMPRWidget::defaultCursor
 * @return
 * 返回默认光标
 */
const QCursor &BPPMPRWidget::defaultCursor() const
{
    return this->DefaultCursor;
}
/**
 * @brief BPPMPRWidget::cleanupContext
 * 清除上下文
 */
void BPPMPRWidget::cleanupContext()
{
    this->RenderWindowAdapter.reset(nullptr);
}
/**
 * @brief BPPMPRWidget::updateSize
 * 更新画布大小
 */
void BPPMPRWidget::updateSize()
{
    if(this->RenderWindowAdapter)
    {
        this->RenderWindowAdapter->resize(this->width(),this->height());
    }
}
/**
 * @brief BPPMPRWidget::event
 * @param evt
 * @return
 * 重载event事件
 */
bool BPPMPRWidget::event(QEvent *evt)
{
    if(this->RenderWindowAdapter)
    {
        this->RenderWindowAdapter->handleEvent(evt);
    }
    return this->Superclass::event(evt);
}
/**
 * @brief BPPMPRWidget::initializeGL
 * 初始化OpenGL
 */
void BPPMPRWidget::initializeGL()
{
    this->Superclass::initializeGL();
    if(this->RenderWindow)
    {
        Q_ASSERT(this->RenderWindowAdapter.data() == nullptr);              //断言，程序错误后会自动停止程序运行，并弹出提示，只有的Debug下有效
        this->RenderWindowAdapter.reset(new QVTKRenderWindowAdapter(this->context(),this->RenderWindow,this));  //重置
        this->RenderWindowAdapter->setDefaultCursor(this->defaultCursor());         //设置默认光标
        this->RenderWindowAdapter->setEnableHiDPI(this->EnableHiDPI);               //设置HiDPI
        this->RenderWindowAdapter->setUnscaledDPI(this->UnscaledDPI);               //设置默认DPI
    }
    this->connect(this->context(),&QOpenGLContext::aboutToBeDestroyed,this,&BPPMPRWidget::cleanupContext,static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::DirectConnection)); //连接信号槽
}
/**
 * @brief BPPMPRWidget::paintGL
 * 绘制
 */
void BPPMPRWidget::paintGL()
{
    this->Superclass::paintGL();
    if(this->RenderWindow)
    {
        Q_ASSERT(this->RenderWindowAdapter);        //断言，程序在出问题是，会停止，并自动弹窗包出错位置，只有的Debug下有效
        this->RenderWindowAdapter->paint();         //调用vtk绘制函数
        this->makeCurrent();                        //自动调用了，见上面注释
        QOpenGLFunctions_3_2_Core* f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_2_Core>();
        if(f)
        {
            const QSize deviceSize = this->size() * this->devicePixelRatioF();
            this->RenderWindowAdapter->blit(this->defaultFramebufferObject(),GL_COLOR_ATTACHMENT0,QRect(QPoint(0,0),deviceSize));
            f->glClearColor(1.0f,1.0f,1.0f,1.0f);
        }
    }
    else
    {
        QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
        f->glClearColor(1.0f,1.0f,1.0f,1.0f);
        f->glClear(GL_COLOR_BUFFER_BIT);
    }
}
