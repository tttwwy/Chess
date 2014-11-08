#include <QApplication>
#include "mainwindow.h"
#include <QTextCodec>

int main(int argc,char *argv[])
{
    QApplication app(argc,argv);   //QT�������,���е�QT����Ҫ����argc,��argv����app
    QTextCodec *code = QTextCodec::codecForName("system");
    QTextCodec::setCodecForTr(code);
    QTextCodec::setCodecForLocale(code);
    QTextCodec::setCodecForCStrings(code);
    MainWindow *t=new MainWindow;                        //����Test��
    t->show();                      //����show����,��ʾ�ô���

    return app.exec();             //������Ϣѭ��
}

