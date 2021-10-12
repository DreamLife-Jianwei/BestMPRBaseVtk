#ifndef BPPMPRWIDGET_H
#define BPPMPRWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class bPPMPRWidget; }
QT_END_NAMESPACE

enum showType
{
    TRA,
    SAG,
    COR
};


class bPPMPRWidget : public QWidget
{
    Q_OBJECT

public:

    int scaleIndex = 0;                             //当前图层
    int scaleCount = 0;                             //图层数
    int scaleThickness = 0;                         //层厚
    int scaleGap = 0;                               //层间距
    QColor imageColor = QColor(255,255,255,255);    //图像颜色


    bool scaleTool = false;                         //比例尺工具
    bool zoomTool = false;                          //放大镜工具
    bool patientInforTool = false;                  //病人信息


   showType showMode= showType::COR;                //显示模式

    bPPMPRWidget(QWidget *parent = nullptr);
    ~bPPMPRWidget();

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



private:
    Ui::bPPMPRWidget *ui;
};
#endif // BPPMPRWIDGET_H
