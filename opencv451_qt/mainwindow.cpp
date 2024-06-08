#include "mainwindow.h"
#include "QVBoxLayout"
#include "QLabel"
#include "opencv2/opencv.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVBoxLayout* layout=new QVBoxLayout();
    QLabel* label=new QLabel();
    std::string str=cv::format("Hello World,QT and OpenCV%d.%d",cv::getVersionMajor(),cv::getVersionMinor());
    label->setText(QString(str.c_str()));
    layout->addWidget(label);
    ui->centralwidget->setLayout(layout);
    cv::Mat src=cv::imread("C:/opencv-4.5.1/sources/samples/data/building.jpg");
    cv::imshow("image show",src);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

MainWindow::~MainWindow()
{
    delete ui;
}

