#include "eveluation.h"

CEveluation::CEveluation()
{
    m_BaseValue[wolf] = BASEVALUE_WOLF;
    m_BaseValue[sheep] = BASEVALUE_SHEEP;
    m_FlexValue[wolf] = FLEXIBILITY_WOLF;
    m_FlexValue[sheep] = FLEXIBILITY_SHEEP;
}
CEveluation::~CEveluation()
{

}
int count = 0;
int CEveluation::Eveluate(byte position[gridNum][gridNum], bool iswolf)
{
    int i,j,k;
    int nChessType,nTargetType;
    count++;
    memset(m_chessValue,0,sizeof(m_chessValue));
    memset(m_AttackPos,0,sizeof(m_AttackPos));
    memset(m_FlexibilityPos,0,sizeof(m_FlexibilityPos));
    for (i = 0;i < gridNum;i++)
        for (j = 0;j < gridNum;j++)
        {
            if (position[i][j] != 0)
            {
                nChessType = position[i][j];
                GetRelatePiece(position,i,j);
                for (k = 0;k < nPosCount;k++)
                {
                    nTargetType = position[RelatePos[k].x()][RelatePos[k].y()];
                    if (nTargetType == 0)
                        m_FlexibilityPos[i][j]++;
                    else
                    {
                        if (nChessType == wolf && nTargetType == sheep)
                        {
                            m_AttackPos[RelatePos[k].x()][RelatePos[k].y()]++;
                            m_FlexibilityPos[i][j]++;
                        }

                    }
                }
                if (nChessType == wolf)
                    m_chessValue[i][j] += m_FlexValue[nChessType] * m_FlexibilityPos[i][j];

            }
        }
    //    for (i = 0;i < gridNum;i++)
    //        for (j = 0;j < gridNum;j++)
    //        {
    //            if (position[i][j] != 0)
    //            {
    //                nChessType = position[i][j];
    //                if (nChessType == wolf)
    //                    m_chessValue[i][j] += m_FlexValue[nChessType] * m_FlexibilityPos[i][j];

    //            }
    //        }
    int nHalfvalue;
    int WolfValue = 0;
    int SheepValue = 0;
    for (i = 0;i < gridNum;i++)
        for (j = 0;j < gridNum;j++)
        {
            if (position[i][j] != 0)
            {
                nChessType = position[i][j];
                nHalfvalue = m_BaseValue[nChessType]/20;
                m_chessValue[i][j] += m_BaseValue[nChessType];
                if (nChessType == sheep)
                {
                    if (m_AttackPos[i][j])
                    {
                        if (!iswolf)
                        {
                            m_chessValue[i][j] -= nHalfvalue * 4;
                        }
                        else
                        {
                            m_chessValue[i][j] -= nHalfvalue * 7;
                        }
                    }
                    SheepValue += m_chessValue[i][j];
                }
                else
                    WolfValue += m_chessValue[i][j];
            }
        }

//    for (i = 0;i < gridNum;i++)
//        for (j = 0;j < gridNum;j++)
//        {
//            nChessType = position[i][j];
//            if (nChessType != 0)
//            {
//                if (nChessType == wolf)
//                    WolfValue += m_chessValue[i][j];
//                else
//                    SheepValue += m_chessValue[i][j];

//            }
//        }
    wolfscore  = WolfValue;
    sheepscore = SheepValue;
    if (iswolf)
        return WolfValue - SheepValue;
    else
        return SheepValue - WolfValue;

}

int CEveluation::GetRelatePiece(byte position[gridNum][gridNum], int i, int j)
{
    nPosCount = 0;
    byte nChessID;   
    int x,y;
    int dis1[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    int dis2[4][2] = {{0,2},{0,-2},{2,0},{-2,0}};
    nChessID = position[i][j];

    if (nChessID == wolf)
    {

        for (int k = 0;k <4;k++)
        {
            x = i +dis1[k][0];
            y = j + dis1[k][1];
            if (x >= 0 && x <gridNum && y >= 0 && y < gridNum )
            {
                if (position[x][y] == 0)
                    AddPoint(x,y);
            }

        }

        for (int k = 0;i < 4;i++)
        {
            x = i +dis2[k][0];
            y = j + dis2[k][1];
            if (x >= 0 && x <gridNum && y >= 0 && y < gridNum )
            {

                if (position[x][y]== sheep)
                {
                    if(position[i+dis1[i][0]][j+dis1[i][1]] == 0)
                        AddPoint(x,y);
                }
            }
        }
    }
    if (nChessID == sheep)
    {
        for (int k = 0;k <4;k++)
        {
            x = i +dis1[k][0];
            y = j + dis1[k][1];
            if (x >= 0 && x <gridNum && y >= 0 && y < gridNum  )
            {
                if (position[x][y] == 0)
                    AddPoint(x,y);
            }

        }
    }
return nPosCount;
}

bool CEveluation::CanTouch(byte position[gridNum][gridNum], QPoint start, QPoint end)
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

void CEveluation::AddPoint(int x, int y)
{
    RelatePos[nPosCount].setX(x) ;
    RelatePos[nPosCount].setY(y) ;

    nPosCount++;
}
