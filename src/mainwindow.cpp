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

    int rb =QMessageBox::warning(this, tr("请确认"), tr("真的要结束这局游戏?"), tr("确定") ,tr("取消"));
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
    QMessageBox::about(this, tr("关于"), tr("狼吃羊1.0\n作者：苦菜花"));
}

void MainWindow::on_help_triggered()
{
    QMessageBox::about(this, tr("帮助"),
                       tr("狼吃羊1.0\n狼吃羊这个游戏流行于我国北方地区，简单益智，广受欢迎。\n行动方式：狼先行动。狼和羊轮流行动，每一回合只能移动一个棋子，一个棋子一次只能移动一格。棋子只能上下左右移动。\n吃子规则：狼可以隔一个空格吃一只羊，相邻则被堵。\n输赢规则：如果狼的四周都被羊围住，无法行动，则狼方失败，反之狼将羊吃尽，则狼方胜。\n"));

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
