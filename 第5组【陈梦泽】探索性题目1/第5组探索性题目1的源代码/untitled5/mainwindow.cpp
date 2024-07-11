#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showstring(long a,long long b,double c,double d,double e)
{
    QString a1=QString::number(a);
    QString b1=QString::number(b);
    QString c1=QString::number(c);
    QString d1=QString::number(d);
    QString e1=QString::number(e);
    expression+="还原图像耗时:";
    expression+=a1.toStdString();
    expression+="ms\n";
    expression+="块数:";
    expression+=b1.toStdString();
    expression+="\n";
    expression+="PSNR值:";
    expression+=c1.toStdString();
    expression+="\n";
    expression+="BPP值:";
    expression+=d1.toStdString();
    expression+="\n";
    expression+="CR值:";
    expression+=e1.toStdString();
    expression+="\n";
    ui->label->setText(expression);
}
