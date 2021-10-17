#ifndef BPPMPRWIDGET_H
#define BPPMPRWIDGET_H

// Qt 基础

#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>                        //继承基类
#include <QScopedPointer>                       //内存管理
#include <QMouseEvent>                          //鼠标事件

// vtk 支持
#include "QVTKInteractorAdapter.h"
#include "QVTKRenderWindowAdapter.h"
#include "vtkCommand.h"
#include "vtkGenericOpenGLRenderWindow.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkObjectFactory.h"
#include "vtkOpenGLState.h"
#include "QVTKInteractor.h"                     //vtk 交互
#include "vtkGUISupportQtModule.h"              //vtk 宏支持
#include "vtkNew.h"                             //vtk New
#include "vtkSmartPointer.h"                    //vtk 智能指针

// 自定义

#include "mprpipeline.h"                        //流水钱管理


QT_BEGIN_NAMESPACE
namespace Ui { class bPPMPRWidget; }
QT_END_NAMESPACE


class QVTKInteractor;
class QVTKInteractorAdapter;
class QVTKRenderWindowAdapter;
class vtkGenericOpenGLRenderWindow;


class bPPMPRWidget : public QOpenGLWidget
{
    Q_OBJECT
    typedef QOpenGLWidget Superclass;

public:

/*********************************************************************************************************/

    // 图像相关

    int scaleIndex = 0;                                         //当前图层
    int scaleCount = 0;                                         //图层数
    int scaleThickness = 0;                                     //层厚
    int scaleGap = 0;                                           //层间距
    QColor imageColor = QColor(255,255,255,255);                //图像颜色

    // 工具相关

    bool scaleTool = false;                                     //比例尺工具
    bool zoomTool = false;                                      //放大镜工具
    bool patientInforTool = false;                              //病人信息

    //基础信息

   showType showMode= showType::COR;                            //显示模式
   mprPipeline *m_mprPipeline;                                  //流水线管理类

/*********************************************************************************************************/

    bPPMPRWidget(QOpenGLWidget *parent = nullptr);
    ~bPPMPRWidget();
    /**
     * @brief setRenderWindow
     * @param win
     * 设置渲染窗口
     */
    void setRenderWindow(vtkGenericOpenGLRenderWindow *win);
    /**
     * @brief setRenderWindow
     * @param win
     * 设置渲染窗口
     */
    void setRenderWindow(vtkRenderWindow *win);
    /**
     * @brief renderWindow
     * @return
     * 返回渲染窗口
     */
    vtkRenderWindow* renderWindow() const;
    /**
     * @brief interator
     * @return
     * 返回交互器
     */
    QVTKInteractor* interator() const;


    VTK_LEGACY(void SetRenderWindow(vtkGenericOpenGLRenderWindow* win));

    VTK_LEGACY(void SetRenderWindow(vtkRenderWindow* win));

    VTK_LEGACY(vtkRenderWindow* GetRenderWindow());
    VTK_LEGACY(QVTKInteractor* GetInteractor());

    VTK_LEGACY(QVTKInteractorAdapter* GetInteractorAdapter());

    VTK_LEGACY(void setQVTKCursor(const QCursor& cursor));

    VTK_LEGACY(void setDefaultQVTKCursor(const QCursor& cursor));

/*********************************************************************************************************/

    /**
     * @brief render
     * 控件开始渲染
     */
    void render();
    /**
     * @brief setData
     * 设置控件数据
     */
    void setData();
    /**
     * @brief save
     * 保存
     */
    void save();
    /**
     * @brief update
     * 更新、刷新
     */
    void update();
    /**
     * @brief setShowMode
     * @param mode
     * 设置显示模式，
     */
    void setShowMode(showType mode = showType::COR);
    /**
     * @brief getScaleIndex
     * @return
     * 获取当前图层
     */
    int getScaleIndex();
    /**
     * @brief setScaleIndex
     * @param index
     * 设置显示图层
     */
    void setScaleIndex(int index = 0);
    /**
     * @brief getScaleCount
     * @return
     * 获取图层数
     */
    int getScaleCount();
    /**
     * @brief setScaleCount
     * @param count
     * 设置图层数，这里应该没有啥实质用途
     */
    void setScaleCount(int count = 0);
    /**
     * @brief getScaleGap
     * @return
     * 获取层间距
     */
    int getScaleGap();
    /**
     * @brief setScaleGat
     * @param gap
     * 设置层间距
     */
    void setScaleGat(int gap = 0);
    /**
     * @brief getScaleThickness
     * @return
     * 获取层厚
     */
    int getScaleThickness();
    /**
     * @brief setScaleThickness
     * @param thickness
     * 设置层厚
     */
    void setScaleThickness(int thickness = 0);
    /**
     * @brief getImageColor
     * @return
     * 获取图像颜色
     */
    QColor getImageColor();
    /**
     * @brief setImageColor
     * @param color
     * 设置图像颜色
     */
    void setImageColor(QColor color = QColor(255,255,255,255));




/*********************************************************************************************************/
protected:
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> RenderWindow;
    QScopedPointer<QVTKRenderWindowAdapter> RenderWindowAdapter;
private:
    Ui::bPPMPRWidget *ui;

    Q_DISABLE_COPY(bPPMPRWidget);       //确保唯一性，私有化拷贝构造函数和赋值操作符

    bool EnableHiDPI;
    int UnscaledDPI;
    QCursor DefaultCursor;

};
#endif // BPPMPRWIDGET_H
