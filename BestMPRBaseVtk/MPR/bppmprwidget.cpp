#include "bppmprwidget.h"
#include "ui_bppmprwidget.h"


bPPMPRWidget::bPPMPRWidget(QOpenGLWidget *parent) : QOpenGLWidget(parent) , ui(new Ui::bPPMPRWidget)
{
    ui->setupUi(this);
    m_mprPipeline = new mprPipeline();      //流水钱管理类


}

bPPMPRWidget::~bPPMPRWidget()
{
    delete ui;
}

void bPPMPRWidget::setRenderWindow(vtkGenericOpenGLRenderWindow *win)
{

}

void bPPMPRWidget::setRenderWindow(vtkRenderWindow *win)
{

}

vtkRenderWindow *bPPMPRWidget::renderWindow() const
{
    return nullptr;
}

QVTKInteractor *bPPMPRWidget::interator() const
{
    return nullptr;
}


void bPPMPRWidget::render()
{
    if(m_mprPipeline)
    {
        m_mprPipeline->render();
    }
}

void bPPMPRWidget::setData()
{

}

void bPPMPRWidget::save()
{

}

void bPPMPRWidget::update()
{

}

void bPPMPRWidget::setShowMode(showType mode)
{

}

int bPPMPRWidget::getScaleIndex()
{
    return 0;
}

void bPPMPRWidget::setScaleIndex(int index)
{

}

int bPPMPRWidget::getScaleCount()
{
return 0;
}

void bPPMPRWidget::setScaleCount(int count)
{

}

int bPPMPRWidget::getScaleGap()
{
return 0;
}

void bPPMPRWidget::setScaleGat(int gap)
{

}

int bPPMPRWidget::getScaleThickness()
{
return 0;
}

void bPPMPRWidget::setScaleThickness(int thickness)
{

}

QColor bPPMPRWidget::getImageColor()
{
    return QColor(0,0,0,0);
}

void bPPMPRWidget::setImageColor(QColor color)
{

}
