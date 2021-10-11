#ifndef BPPMPRWIDGET_H
#define BPPMPRWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class bPPMPRWidget; }
QT_END_NAMESPACE

class bPPMPRWidget : public QWidget
{
    Q_OBJECT

public:
    bPPMPRWidget(QWidget *parent = nullptr);
    ~bPPMPRWidget();

private:
    Ui::bPPMPRWidget *ui;
};
#endif // BPPMPRWIDGET_H
