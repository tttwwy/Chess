#include "cnegamaxengine.h"

CNegamaxEngine::CNegamaxEngine()
{
}

CNegamaxEngine::~CNegamaxEngine()
{
}

void CNegamaxEngine::SearchAGoodMove(byte position[gridNum][gridNum], bool iswolf)
{
    m_nMaxDepth = m_nSearchDepth;
    memcpy(CurPosition,position,gridNum*gridNum);
    score = NegaMax(m_nMaxDepth,iswolf);
}
void CNegamaxEngine::stop()
{

}

int CNegamaxEngine::NegaMax(int depth,bool iswolf)
{
    int current = -20000;
    int score;
    int Count,i;
    byte type;
    i = IsGameOver(CurPosition,depth,iswolf);
    if (i!=0)
        return i;
    if (depth <= 0)
        return m_pEval->Eveluate(CurPosition,iswolf);
    Count = m_pMG->CreatePossibleMove(CurPosition,depth,iswolf);
    for (i = 0;i < Count;i++)
    {
        type = MakeMove(&m_pMG->m_MoveList[depth][i]);
        score = -NegaMax(depth-1,!iswolf);
        UnMakeMove(&m_pMG->m_MoveList[depth][i],type);
        if (score > current)
        {
            current = score;
            if (depth == m_nMaxDepth)
            {
                m_cmBestMove = m_pMG->m_MoveList[depth][i];
            }
        }
    }
    return current;
}
