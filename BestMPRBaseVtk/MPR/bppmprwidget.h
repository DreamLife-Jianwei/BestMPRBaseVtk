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

private:
    Ui::bPPMPRWidget *ui;
};
#endif // BPPMPRWIDGET_H
