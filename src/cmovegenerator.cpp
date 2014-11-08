#include "cmovegenerator.h"

CMoveGenerator::CMoveGenerator()
{
}

CMoveGenerator::~CMoveGenerator()
{


}

bool CMoveGenerator::IsValidMove(byte position[gridNum][gridNum], QPoint start, QPoint end)
{
    int dis1[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    int dis2[4][2] = {{0,2},{0,-2},{2,0},{-2,0}};
    if (start.x() >= 0 && start.x() <gridNum && start.y() >= 0 && start.y() < gridNum && end.x() >= 0 && end.x() <gridNum && end.y() >= 0 && end.y() < gridNum )
    {
        if (position[start.x()][start.y()] == wolf)
        {
            for (int i = 0;i < 4;i++)
            {
                if (start.x()+ dis1[i][0] == end.x() && start.y() + dis1[i][1]==end.y())
                {
                    if (position[end.x()][end.y()]== 0)
                        return true;
                    else
                        return false;
                }
            }
            for (int i = 0;i < 4;i++)
            {
                if (start.x()+ dis2[i][0] == end.x() && start.y() + dis2[i][1]==end.y())
                {
                    if (position[end.x()][end.y()]== 0)
                        return false;
                    if (position[end.x()][end.y()]== sheep)
                    {
                        if(position[start.x()+dis1[i][0]][start.y()+dis1[i][1]] == 0)
                            return true;
                        else
                            return false;
                    }
                }
            }
            return false;
        }

        if (position[start.x()][start.y()]== sheep)
        {
            for (int i = 0;i < 4;i++)
            {
                if (start.x()+ dis1[i][0] == end.x() && start.y() + dis1[i][1] == end.y())
                {
                    if (position[end.x()][end.y()]== 0)
                        return true;
                }
            }
            return false;
        }
    }

    return false;
}
//false ÎªÑò£¬trueÎªÀÇ
int CMoveGenerator::CreatePossibleMove(byte position[gridNum][gridNum], int nPly, int nSide)
{

    int nChessID;


    m_nMoveCount = 0;
    for (int i = 0;i < gridNum;i++)
        for (int j = 0;j < gridNum;j++)
        {
            if (position[i][j] != 0)
            {
                nChessID = position[i][j];
                if (nSide && nChessID == sheep)
                    continue;
                if (!nSide && nChessID == wolf)
                    continue;
                switch(nChessID)
                {
                case wolf:
                    Gen_WolfMove(position,i,j,nPly);
                    break;
                case sheep:
                    Gen_SheepMove(position,i,j,nPly);
                    break;
                default:
                    break;
                }
            }
        }
    return m_nMoveCount;

}

int CMoveGenerator::AddMove(QPoint start, QPoint end, int nPly)
{
    m_MoveList[nPly][m_nMoveCount].start = start;
    m_MoveList[nPly][m_nMoveCount].end = end;
    m_nMoveCount++;
    return m_nMoveCount;
}

void CMoveGenerator::Gen_WolfMove(byte position[gridNum][gridNum], int x, int y, int nPly)
{
    int dis1[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    int dis2[4][2] = {{0,2},{0,-2},{2,0},{-2,0}};
    QPoint start = QPoint(x,y);
    for (int i = 0;i <4;i++)
    {

        if (IsValidMove(position,start,QPoint(start.x()+dis2[i][0],start.y() + dis2[i][1])))
        {
            AddMove(start,QPoint(start.x()+dis2[i][0],start.y() + dis2[i][1]),nPly);
        }
        if (IsValidMove(position,start,QPoint(start.x()+dis1[i][0],start.y() + dis1[i][1])))
        {
            AddMove(start,QPoint(start.x()+dis1[i][0],start.y() + dis1[i][1]),nPly);
        }

    }

}

void CMoveGenerator::Gen_SheepMove(byte position[gridNum][gridNum], int x, int y, int nPly)
{
    int dis1[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    QPoint start = QPoint(x,y);
    for (int i = 0;i <4;i++)
    {
        if (IsValidMove(position,start,QPoint(start.x()+dis1[i][0],start.y() + dis1[i][1])))
        {
            AddMove(start,QPoint(start.x()+dis1[i][0],start.y() + dis1[i][1]),nPly);
        }

    }
}
