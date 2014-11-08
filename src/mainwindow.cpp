#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    Config = new config;
    information = new Score;
    setupUi(this);
    undo->setEnabled(false);

    connect(board,SIGNAL(isundo(bool)),undo,SLOT(setEnabled(bool)));
    connect(board,SIGNAL(isredo(bool)),redo,SLOT(setEnabled(bool)));
    connect(board,SIGNAL(isstart(bool)),stop,SLOT(setEnabled(bool)));
    connect(Config,SIGNAL(configChange(int,int,int)),board,SLOT(setConfig(int,int,int)));
    connect(board,SIGNAL(winner(bool)),information,SLOT(is_win(bool)));

    bells =  new QSound("music/yang.wav");
    bells->setLoops(-1);

}

void MainWindow::showConfig()
{

    Config->show();
}

void MainWindow::MusicOn()
{

}

void MainWindow::MusicOff()
{
}

MainWindow::~MainWindow()
{

}



void MainWindow::on_newGame_triggered()
{
    stop->setEnabled(true);
    undo->setEnabled(false);
    redo->setEnabled(false);
    board->gameStart();


}

void MainWindow::on_stop_triggered()
{

    int rb =QMessageBox::warning(this, tr("��ȷ��"), tr("���Ҫ���������Ϸ?"), tr("ȷ��") ,tr("ȡ��"));
    if(rb ==0)
    {
        board->setstartflag(0);
        stop->setEnabled(false);
        redo->setEnabled(false);
        undo->setEnabled(false);
    }

}

void MainWindow::on_undo_triggered()
{
    board->restoreStep(true);
    if (Config->IsComputer())
        board->restoreStep(true);

}


void MainWindow::on_about_triggered()
{
    QMessageBox::about(this, tr("����"), tr("�ǳ���1.0\n���ߣ���˻�"));
}

void MainWindow::on_help_triggered()
{
    QMessageBox::about(this, tr("����"),
                       tr("�ǳ���1.0\n�ǳ��������Ϸ�������ҹ����������������ǣ����ܻ�ӭ��\n�ж���ʽ�������ж����Ǻ��������ж���ÿһ�غ�ֻ���ƶ�һ�����ӣ�һ������һ��ֻ���ƶ�һ������ֻ�����������ƶ���\n���ӹ����ǿ��Ը�һ���ո��һֻ�������򱻶¡�\n��Ӯ��������ǵ����ܶ�����Χס���޷��ж������Ƿ�ʧ�ܣ���֮�ǽ���Ծ������Ƿ�ʤ��\n"));

}

void MainWindow::on_redo_triggered()
{

    board->restoreStep(false);
    if (Config->IsComputer())
        board->restoreStep(false);

}




void MainWindow::on_set_triggered()
{
    showConfig();
}

void MainWindow::on_OpenFile_triggered()
{
    board->fileRead();
}

void MainWindow::on_SaveFile_triggered()
{
    board->fileWrite();
}

void MainWindow::on_action_triggered()
{

    if (!bells->isFinished())
        bells->stop();
    else
        bells->play();

}

void MainWindow::on_information_triggered()
{
    information->show();
}

void MainWindow::on_hint_triggered()
{
    board->help();
}
