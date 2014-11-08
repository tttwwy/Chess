#ifndef CHESSBOARD_H
#define CHESSBOARD_H


#include <QPoint>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QStack>
#include "define.h"
#include "cmovegenerator.h"
#include "csearchengine.h"
#include "cnegamaxengine.h"
#include "eveluation.h"
#include <QFileDialog>



class chessboard : public QWidget
{
    Q_OBJECT
public:
    chessboard(QWidget *parent = 0);
    void setstartflag(int flag);
    int getStartflag();

    void chessBoard_Init();


    void paintEvent(QPaintEvent *painter);
    void drawBoard(QPainter &painter);
    void drawChess(QPainter &painter);
    void drawSquare(QPainter &painter,QPoint point,Qt::GlobalColor style);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void updateWolf();
    void move(QPoint start,QPoint end);
    void setMousestate();

    int isOver();
    void gameOver(int result);
    void gameStart();
    void computerMove();
    void nextStep();
    bool checkboard(int x,int y);
    void saveStep();
    bool restoreStep(bool direction);
    bool fileRead();
    bool fileWrite();
    int undoSize();

private:

    byte board[gridNum][gridNum];
    QStack<step> undo;
    QStack<step> redo;
    int player[3];
    int hardness;//游戏难度
    int startflag;//程序开始的标志
    int state;//当前的行动方
    int gridSize;
    int mousestate;//鼠标状态






    QPoint start;//选中的点
    QPoint end;//目标点


    CSearchEngine *m_pSE;
    CMoveGenerator * pMG;
    CEveluation * pEvel;



signals:
    void isundo(bool);
    void isredo(bool);
    void isstart(bool);
    void winner(bool);


public slots:
    void setConfig(int ,int,int);
    void help();

};

#endif // CHESSBOARD_H
