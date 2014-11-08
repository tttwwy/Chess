#include <QApplication>
#include "mainwindow.h"
#include <QTextCodec>

int main(int argc,char *argv[])
{
    QApplication app(argc,argv);   //QT程序入口,所有的QT程序都要根据argc,和argv生成app
    QTextCodec *code = QTextCodec::codecForName("system");
    QTextCodec::setCodecForTr(code);
    QTextCodec::setCodecForLocale(code);
    QTextCodec::setCodecForCStrings(code);
    MainWindow *t=new MainWindow;                        //生成Test类
    t->show();                      //调用show方法,显示该窗口

    return app.exec();             //进入消息循环
}

