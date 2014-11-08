#ifndef CMOVEGENERATOR_H
#define CMOVEGENERATOR_H
#include "define.h"

class CMoveGenerator
{
public:
    CMoveGenerator();
    virtual ~CMoveGenerator();
    static bool IsValidMove(byte position[gridNum][gridNum],QPoint start,QPoint end);
    int CreatePossibleMove(byte position[gridNum][gridNum],int nPly,int nSide);
    ChessMove m_MoveList[11][40];
protected:
    int AddMove(QPoint start,QPoint end,int nPly);
    void Gen_WolfMove(byte position[gridNum][gridNum],int x,int y,int nPly);
    void Gen_SheepMove(byte position[gridNum][gridNum],int x,int y,int nPly);
    int m_nMoveCount;//记录走法数量
};

#endif // CMOVEGENERATOR_H
