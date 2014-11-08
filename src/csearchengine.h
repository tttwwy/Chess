#ifndef CSEARCHENGINE_H
#define CSEARCHENGINE_H
#include "define.h"
#include "eveluation.h"
#include "cmovegenerator.h"
#include <QThread>
class CSearchEngine
{
public:
    CSearchEngine();
    virtual ~CSearchEngine();
    virtual void SearchAGoodMove(byte position[gridNum][gridNum],bool iswolf) = 0;
    virtual void stop() = 0;

    void SetSearchDeepth(int nDepth){m_nSearchDepth = nDepth;};
    void SetEveluator(CEveluation * pEval){m_pEval = pEval;};
    void SetMoveGenerator(CMoveGenerator *pMG){m_pMG = pMG;};
    ChessMove m_cmBestMove;
    int score;
protected:
    byte MakeMove(ChessMove * move);
    void UnMakeMove(ChessMove * move,byte ChessID);
    int IsGameOver(byte position[gridNum][gridNum],int nDepth,bool iswolf);

    byte CurPosition[gridNum][gridNum];
//    ChessMove m_cmBestMove;

    //走法产生器指针
    CMoveGenerator * m_pMG;
    CEveluation * m_pEval;
    int m_nSearchDepth;
    int m_nMaxDepth;

};

#endif // CSEARCHENGINE_H
