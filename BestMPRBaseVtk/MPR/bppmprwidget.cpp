#include "bppmprwidget.h"
#include "ui_bppmprwidget.h"

bPPMPRWidget::bPPMPRWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::bPPMPRWidget)
{
    ui->setupUi(this);
}

bPPMPRWidget::~bPPMPRWidget()
{
    delete ui;
}

