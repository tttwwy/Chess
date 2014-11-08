#ifndef CNEGAMAXENGINE_H
#define CNEGAMAXENGINE_H
#include "define.h"
#include "csearchengine.h"
#include "string.h"
class CNegamaxEngine:public CSearchEngine
{
public:
    CNegamaxEngine();
    virtual ~CNegamaxEngine();
    virtual void stop();

    virtual void SearchAGoodMove(byte position[gridNum][gridNum],bool iswolf);
protected:
    int NegaMax(int depth, bool iswolf);

};

#endif // CNEGAMAXENGINE_H
