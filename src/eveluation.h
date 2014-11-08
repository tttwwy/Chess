#ifndef EVELUATION_H
#define EVELUATION_H
#include "define.h"
#define BASEVALUE_WOLF 0
#define BASEVALUE_SHEEP 100
#define FLEXIBILITY_WOLF 20
#define FLEXIBILITY_SHEEP 0
#include <cstring>

class CEveluation
{
public:
    CEveluation();
    virtual ~CEveluation();
    int wolfscore;
    int sheepscore;

    virtual int Eveluate(byte position[gridNum][gridNum],bool iswolf);
protected:

   //列举与指定位置相关的棋子
   int GetRelatePiece(byte position[gridNum][gridNum],int i,int j);
   //判断位置from的棋子能否走到位置to
   bool CanTouch(byte position[gridNum][gridNum],QPoint start,QPoint end);
   //将一个位置加入相关位置队列
   void AddPoint(int x,int y);
   int m_BaseValue[3];//存放棋子基本价值
   int m_FlexValue[3];//存放棋子灵活性分数的数组
   short m_AttackPos[gridNum][gridNum];//存放所有位置被威胁的信息
   byte m_FlexibilityPos[gridNum][gridNum];//存放所有位置棋子灵活性分数
   int m_chessValue[gridNum][gridNum];//存放每一个棋子的总价值
   int nPosCount;//记录一棋子相关位置的人数
   QPoint RelatePos[20];//记录一个棋子相关位置的数组



};

#endif // EVELUATION_H
