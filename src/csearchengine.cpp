#include "csearchengine.h"

CSearchEngine::CSearchEngine()
{


}

CSearchEngine::~CSearchEngine()
{
    delete m_pMG;
    delete m_pEval;
}

byte CSearchEngine::MakeMove(ChessMove *move)
{
    byte nChessID;
    nChessID = CurPosition[move->end.x()][move->end.y()];
    CurPosition[move->end.x()][move->end.y()] = CurPosition[move->start.x()][move->start.y()];
    CurPosition[move->start.x()][move->start.y()] = 0;
    return nChessID;
}

void CSearchEngine::UnMakeMove(ChessMove *move, byte ChessID)
{
    CurPosition[move->start.x()][move->start.y()] = CurPosition[move->end.x()][move->end.y()];
    CurPosition[move->end.x()][move->end.y()] = ChessID;
}

int CSearchEngine::IsGameOver(byte position[gridNum][gridNum], int nDepth,bool iswolf)
{

    bool WolfLive = false,SheepLive = false;
    int SheepNum = 0;

    int dis[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};


    for (int i = 0;i<gridNum;i++)
        for (int j = 0;j<gridNum;j++)
        {
            if (position[i][j] == wolf)
            {
                for (int k = 0;k < 4;k++)
                {
                    if (i+dis[k][0] >=0
                            && i + dis[k][0] < gridNum
                            && j + dis[k][1] >= 0
                            && j + dis[k][1] < gridNum
                            && position[i+dis[k][0]][j+dis[k][1]] == 0)
                    {

                        WolfLive = true;
                        break;
                    }
                }
            }
            if (position[i][j] == sheep)
            {
                SheepNum++;
            }
        }

    if (SheepNum >= 3)
        SheepLive = true;

    if (!WolfLive)
    {
        if (!iswolf)
            return 19990 + nDepth;
        else
            return -19990 - nDepth;
    }
    else if (!SheepLive)
    {
        if (!iswolf)
            return -19990 - nDepth;
        else
            return 19990 + nDepth;
    }
    return 0;
}
