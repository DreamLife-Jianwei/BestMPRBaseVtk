#include "bppmprwidget.h"
#include <QtDebug>

#include <QApplication>
#include <QDesktopWidget>
#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_2_Core>
#include <QOpenGLTexture>
#include <QPointer>
#include <QScopedValueRollback>

#include "QVTKInteractor.h"
#include "QVTKInteractorAdapter.h"
#include "QVTKRenderWindowAdapter.h"
#include "vtkCommand.h"
#include "vtkGenericOpenGLRenderWindow.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkNew.h"
#include "vtkObjectFactory.h"
#include "vtkOpenGLState.h"
#include "vtkSmartPointer.h"

#include "myvtkinteractorstyleimage.h"                  //交互样式


/**
 * @brief BPPMPRWidget::BPPMPRWidget
 * @param parent
 * @param f
 * 构造函数，调用另一个构造函数
 */
BPPMPRWidget::BPPMPRWidget(QWidget *parent, Qt::WindowFlags f) :
    BPPMPRWidget(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New().GetPointer(),parent,f)
{
}
/**
 * @brief BPPMPRWidget::BPPMPRWidget
 * @param window
 * @param parent
 * @param f
 * 最终的构造函数，完成控件焦点设置，
 */
BPPMPRWidget::BPPMPRWidget(vtkGenericOpenGLRenderWindow *window, QWidget *parent, Qt::WindowFlags f) :
    Superclass(parent,f),RenderWindow(nullptr),RenderWindowAdapter(nullptr),EnableHiDPI(true),UnscaledDPI(72),DefaultCursor(QCursor(Qt::ArrowCursor))
{

    m_PipeLine = ImagePipeLine::New();

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
    this->cleanupContext();             //清除上下文
}
/**
 * @brief BPPMPRWidget::setRenderWindow
 * @param win
 * 设置渲染窗口
 */
void BPPMPRWidget::setRenderWindow(vtkGenericOpenGLRenderWindow *win)
{
    if(this->RenderWindow == win)                                                       //判断当前窗口是不是传进来的，是就返回不是继续
    {
        return;
    }

    if(this->RenderWindowAdapter)                                                       // 这将释放所有与旧窗口相关的OpenGL资源
    {
        this->makeCurrent();                                                            //为窗口绘制OpenGL内容做准备，将上下文设置为当前，并为该上下文绑定framebuffer
        this->RenderWindowAdapter.reset(nullptr);                                       //删除并重置指针
    }

    this->RenderWindow = win;                                                           //赋新值
    if(this->RenderWindow)
    {
        this->RenderWindow->SetReadyForRendering(false);

        if(!this->RenderWindow->GetInteractor())                                        //如果没有提供交互器，我们默认将创建一个
        {
            vtkNew<QVTKInteractor> iren;                                                //创建一个默认交互器
            this->RenderWindow->SetInteractor(iren);                                    //为RenderWindow添加交互器

            iren->Initialize();                                                         //交互器初始化

            vtkNew<myVtkInteractorStyleImage> style;                                    //设置交互器默认样式

            style->SetImageViewer(m_PipeLine);

            style->SetBPPMPRWidget(this);

            iren->SetInteractorStyle(style);                                            //设置交互器

        }
        if(this->isValid())
        {
            this->makeCurrent();                                                        //为窗口绘制OpenG内容做准备，将上下文设置为当前，并为该上下文绑定framebuffer paintGL会自动调用。
            this->initializeGL();                                                       //初始化Openg
            this->updateSize();                                                         //更新窗口尺寸
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
    return this->RenderWindow;                                                                                          //返回窗口指针
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
 * @return 返回QSurfaceFormat
 */
QSurfaceFormat BPPMPRWidget::defaultFormat(bool stereo_capable)
{
    return QVTKRenderWindowAdapter::defaultFormat(stereo_capable);                                                      //返回默认QSurfaceFormat
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
        this->RenderWindowAdapter->setEnableHiDPI(enable);                                                              //设置开启窗口高Dpi支持
    }
}
/**
 * @brief BPPMPRWidget::enableHiDPI
 * @return
 * 返回高DPI状态
 */
bool BPPMPRWidget::enableHiDPI() const
{
    return this->EnableHiDPI;                                                                                           //返回高Dpi支持状态
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
        this->RenderWindowAdapter->setUnscaledDPI(dpi);                                                                 //设置默认Dpi
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
 * @brief setInputData
 * @param data 输入数据
 * 设置输入数据
 */
void BPPMPRWidget::setInputData(vtkImageData *data)
{
    m_PipeLine->setInputData(data);
    if(m_PipeLine->getRenderWindow() != this->renderWindow())
        m_PipeLine->setRenderWindow(this->renderWindow());                          //问题已修正，整导入数据的时候切换渲染窗口，但是这么写会不会有新的问题，还待考证
}
/**
 * @brief setInputConnection
 * @param input
 * 设置输入数据
 */
void BPPMPRWidget::setInputConnection(vtkAlgorithmOutput *input)
{
    m_PipeLine->setInputConnection(input);
}
/**
 * @brief render
 * 开始渲染
 */
void BPPMPRWidget::render()
{
    m_PipeLine->render();
}
/**
 * @brief getSliceOrientation
 * @return
 * 获取切片方向
 */
int BPPMPRWidget::getSliceOrientation()
{
    return m_PipeLine->getSliceOrientation();
}
/**
 * @brief ImagePipeLine::setSliceOrientation
 * @param orientation
 * 设置切片方向
 */
void BPPMPRWidget::setSliceOrientation(int orientation)
{
    m_PipeLine->setSliceOrientation(orientation);
}
/**
 * @brief setSliceOrientationToXY
 * 设置切片方向
 */
void BPPMPRWidget::setSliceOrientationToXY()
{
    m_PipeLine->setSliceOrientationToXY();
}
/**
 * @brief setSliceOrientationToXY
 * 设置切片方向
 */
void BPPMPRWidget::setSliceOrientationToYZ()
{
    m_PipeLine->setSliceOrientationToYZ();
}
/**
 * @brief setSliceOrientationToXY
 * 设置切片方向
 */
void BPPMPRWidget::setSliceOrientationToXZ()
{
    m_PipeLine->setSliceOrientationToXZ();
}
/**
 * @brief ImagePipeLine::getSlice
 * @return
 * 获取图像序列
 */
int BPPMPRWidget::getSlice()
{
    return m_PipeLine->getSlice();
}
/**
 * @brief ImagePipeLine::setSlice
 * @param s
 * 设置图像序列
 */
void BPPMPRWidget::setSlice(int slice)
{
    m_PipeLine->setSlice(slice);
}
/**
 * @brief updateDisplayExtent
 * 更新显示范围
 */
void BPPMPRWidget::updateDisplayExtent()
{
    m_PipeLine->updateDisplayExtent();
}
/**
 * @brief getSliceMin
 * @return
 * 获取最小切片
 */
int BPPMPRWidget::getSliceMin()
{
    return m_PipeLine->getSliceMin();
}
/**
 * @brief getSliceMax
 * @return
 * 获取最大切片
 */
int BPPMPRWidget::getSliceMax()
{
    return m_PipeLine->getSliceMax();
}
/**
 * @brief getSliceRange
 * @param range
 * 获取切片范围
 */
void BPPMPRWidget::getSliceRange(int range[])
{
    m_PipeLine->getSliceRange(range);
}
/**
 * @brief getSliceRange
 * @param min
 * @param max
 * 获取切片范围
 */
void BPPMPRWidget::getSliceRange(int &min, int &max)
{
    m_PipeLine->getSliceRange(min,max);
}
/**
 * @brief getSliceRange
 * @return
 * 获取切片范围
 */
int *BPPMPRWidget::getSliceRange()
{
    return m_PipeLine->getSliceRange();
}
/**
 * @brief getColorWindow
 * @return
 * 获取窗宽
 */
double BPPMPRWidget::getColorWindow()
{
    this->colorWindow = m_PipeLine->getColorWindow();
    return this->colorWindow;
}
/**
 * @brief getColorLevel
 * @return
 * 获取窗位
 */
double BPPMPRWidget::getColorLevel()
{
    this->colorLevel = m_PipeLine->getColorLevel();
    return this->colorLevel;
}
/**
 * @brief setColorWindow
 * @param s
 * 设置窗宽
 */
void BPPMPRWidget::setColorWindow(double s)
{
    m_PipeLine->setColorWindow(s);
    emit colorWindowChanged(s);                     //触发窗宽改变信号
}
/**
 * @brief setColorLevel
 * @param s
 * 设置窗位
 */
void BPPMPRWidget::setColorLevel(double s)
{
    m_PipeLine->setColorLevel(s);
    emit colorLevelChanged(s);                      //处罚窗位改变信号
}
/**
 * @brief setDisplayId
 * @param a
 * 设置显示ID
 */
void BPPMPRWidget::setDisplayId(void *a)
{
    m_PipeLine->setDisplayId(a);
}
/**
* @brief setWindowId
* @param a
* 设置窗口ID
*/
void BPPMPRWidget::setWindowId(void *a)
{
    m_PipeLine->setWindowId(a);
}
/**
 * @brief setParentId
 * @param a
 * 设置父窗口ID
 */
void BPPMPRWidget::setParentId(void *a)
{
    m_PipeLine->setParentId(a);
}
/**
 * @brief getPosition
 * @return
 * 获取位置
 */
int *BPPMPRWidget::getPosition()
{
    return m_PipeLine->getPosition();
}
/**
 * @brief setPosition
 * @param x
 * @param y
 * 设置位置
 */
void BPPMPRWidget::setPosition(int x, int y)
{
    m_PipeLine->setPosition(x,y);
}
/**
 * @brief setPosition
 * @param a
 * 设置位置
 */
void BPPMPRWidget::setPosition(int a[])
{
    m_PipeLine->setPosition(a);
}
/**
 * @brief getSize
 * @return
 * 获取尺寸
 */
int *BPPMPRWidget::getSize()
{
    return m_PipeLine->getSize();
}
/**
 * @brief setSize
 * @param width
 * @param height
 * 设置尺寸
 */
void BPPMPRWidget::setSize(int width, int height)
{
    m_PipeLine->setSize(width,height);
}
/**
 * @brief setSize
 * @param a
 * 设置尺寸
 */
void BPPMPRWidget::setSize(int a[])
{
    m_PipeLine->setSize(a);
}
/**
 * @brief setRenderer
 * @param arg
 * 设置渲染器
 */
void BPPMPRWidget::setRenderer(vtkRenderer *arg)
{
    m_PipeLine->setRenderer(arg);
}
/**
 * @brief getRenderWindow
 * @return
 * 获取渲染窗口
 */
vtkRenderWindow *BPPMPRWidget::getRenderWindow()
{
    return this->RenderWindow;
}
/**
 * @brief getRenderer
 * @return
 * 获取渲染器
 */
vtkRenderer *BPPMPRWidget::getRenderer()
{
    return m_PipeLine->getRenderer();
}
/**
 * @brief getImageActor
 * @return
 * 获取ImageActor
 */
vtkImageActor *BPPMPRWidget::getImageActor()
{
    return m_PipeLine->getImageActor();
}
/**
 * @brief getWindowLevel
 * @return
 * 获取窗位
 */
vtkImageMapToWindowLevelColors *BPPMPRWidget::getWindowLevel()
{
    return m_PipeLine->getWindowLevel();
}
/**
 * @brief getInteratorStyle
 * @return
 * 获取交互器
 */
vtkInteractorStyleImage *BPPMPRWidget::getInteratorStyle()
{
    return m_PipeLine->getInteratorStyle();
}
/**
 * @brief setupInteractor
 * @param arg
 * 设置交互器
 */
void BPPMPRWidget::setupInteractor(vtkRenderWindowInteractor *arg)
{
    m_PipeLine->setupInteractor(arg);
}
/**
 * @brief setOffScreenRendering
 * @param i
 * 设置离屏渲染开关
 */
void BPPMPRWidget::setOffScreenRendering(vtkTypeBool i)
{
    m_PipeLine->setOffScreenRendering(i);
}
/**
 * @brief getOffScreenRendering
 * @return
 * 获取离屏渲染状态
 */
vtkTypeBool BPPMPRWidget::getOffScreenRendering()
{
    return m_PipeLine->getOffScreenRendering();
}
/**
 * @brief offScreenRenderingOn
 * 打开离屏渲染
 */
void BPPMPRWidget::offScreenRenderingOn()
{
    m_PipeLine->offScreenRenderingOn();
}
/**
 * @brief offScreenRenderingOff
 * 关闭离屏渲染
 */
void BPPMPRWidget::offScreenRenderingOff()
{
    m_PipeLine->offScreenRenderingOff();
}
/**
 * @brief update
 * 界面更新函数
 */
void BPPMPRWidget::update()
{
    QOpenGLWidget::update();
    m_PipeLine->render();
}
/**
 * @brief mousePressEvent
 * @param event
 * 鼠标按下事件
 */
void BPPMPRWidget::mousePressEvent(QMouseEvent *event)
{

}
/**
 * @brief mouseMoveEvent
 * @param event
 * 鼠标移动事件
 */
void BPPMPRWidget::mouseMoveEvent(QMouseEvent *event)
{

}
/**
 * @brief mouseReleaseEvent
 * @param event
 * 鼠标松开事件
 */
void BPPMPRWidget::mouseReleaseEvent(QMouseEvent *event)
{

}
/**
 * @brief mouseDoubleClickEvent
 * @param event
 * 鼠标双击事件
 */
void BPPMPRWidget::mouseDoubleClickEvent(QMouseEvent *event)
{

}
/**
 * @brief wheelEvent
 * @param event
 * 鼠标滚轮事件
 */
void BPPMPRWidget::wheelEvent(QWheelEvent *event)
{

    this->minSLice = m_PipeLine->getSliceMin();                     //获取最小Slice
    this->maxSlice = m_PipeLine->getSliceMax();                     //获取最大Slice
    this->slice = this->m_PipeLine->getSlice();                     //获取当前Slice
    if(event->delta() > 0)                                          //向前
    {
        if (this->slice > this->minSLice)
        {
            this->slice -= 1;
            this->m_PipeLine->setSlice(this->slice);
            this->m_PipeLine->render();
            emit onSliceChanged(this->slice);
        }
    }
    else                                                            //向后
    {
        if (this->slice < this->maxSlice)
        {
            this->slice += 1;
            this->m_PipeLine->setSlice(this->slice);
            this->m_PipeLine->render();
            emit onSliceChanged(this->slice);
        }
    }
}
/**
 * @brief keyPressEvent
 * @param event
 * 键盘按键按下事件
 */
void BPPMPRWidget::keyPressEvent(QKeyEvent *event)
{

}
/**
 * @brief keyReleaseEvent
 * @param event
 * 键盘按键松开事件
 */
void BPPMPRWidget::keyReleaseEvent(QKeyEvent *event)
{

}
/**
 * @brief enterEvent
 * @param event
 * 进入事件
 */
void BPPMPRWidget::enterEvent(QEvent *event)
{

}
/**
 * @brief leaveEvent
 * @param event
 * 离开事件
 */
void BPPMPRWidget::leaveEvent(QEvent *event)
{

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
    this->connect(this->context(),&QOpenGLContext::aboutToBeDestroyed,
                  this,&BPPMPRWidget::cleanupContext,static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::DirectConnection)); //连接信号槽
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
/**
 * @brief BPPMPRWidget::emitPositionChangedSignal
 * @param temp
 * 发送鼠标位置改变信号
 */
void BPPMPRWidget::emitPositionChangedSignal(int *temp)
{
    emit onPositonChanged(temp[0],temp[1]);
}

