#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QProcess>
#include <QString>
#include <QProcess>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pthButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, QObject::tr("Open File"), QDir::homePath(), QObject::tr("All Files (*)"));
    ui->pthEdit->setText(filePath);

}


void Widget::on_diagButton_clicked()
{
    std::string command=std::string("untitled4.exe ");
    std::string pth=ui->pthEdit->text().toStdString();
    std::string cpcmd="copy /y "+pth+" D:\\Qt\\opencv\\untitled4\\build\\Desktop_Qt_6_5_3_MSVC2019_64bit-Release\\release";
    command+=pth+" "+ui->frameEdit->text().toStdString()+" "+ui->resEdit->text().toStdString()+" "+ui->epsEdit->text().toStdString();
    char charCmd[500];
    command.copy(charCmd,command.size());
    charCmd[command.size()]='\0';
    char cp[500];
    cpcmd.copy(cp,cpcmd.size());
    cp[cpcmd.size()]='\0';

    QProcess process;
    process.start("cmd.exe");
    process.waitForStarted();



    process.write(cp);
    process.write("\n");

    process.write("D:");
    process.write("\n");
    process.write("cd D:\\Qt\\opencv\\untitled4\\build\\Desktop_Qt_6_5_3_MSVC2019_64bit-Release\\release");
    process.write("\n");
    process.write(charCmd);
    process.write("\n");

    process.closeWriteChannel();
    process.waitForFinished();
    QString output = process.readAllStandardOutput();

    qDebug() << output;
}


void Widget::on_horiButton_clicked()
{
    std::string command=std::string("untitled5.exe ");
    std::string pth=ui->pthEdit->text().toStdString();
    std::string cpcmd="copy /y "+pth+" D:\\Qt\\opencv\\untitled5\\build\\Desktop_Qt_6_5_3_MSVC2019_64bit-Release\\release";
    command+=pth+" "+ui->frameEdit->text().toStdString()+" "+ui->resEdit->text().toStdString()+" "+ui->epsEdit->text().toStdString();
    char charCmd[500];
    command.copy(charCmd,command.size());
    charCmd[command.size()]='\0';
    char cp[500];
    cpcmd.copy(cp,cpcmd.size());
    cp[cpcmd.size()]='\0';

    QProcess process;
    process.start("cmd.exe");
    process.waitForStarted();



    process.write(cp);
    process.write("\n");

    process.write("D:");
    process.write("\n");
    process.write("cd D:\\Qt\\opencv\\untitled5\\build\\Desktop_Qt_6_5_3_MSVC2019_64bit-Release\\release");
    process.write("\n");
    process.write(charCmd);
    process.write("\n");

    process.closeWriteChannel();
    process.waitForFinished();
    QString output = process.readAllStandardOutput();

    qDebug() << output;
}

