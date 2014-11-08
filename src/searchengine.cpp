#include "searchengine.h"

SearchEngine::SearchEngine()
{
}

void SearchEngine::setEngine(int id)
{
    this->id = id;
}

step SearchEngine::nextStep(int board[gridNum][gridNum], int state)
{
    step temp;
    if (id == 0)
    {
        Easy a;
        temp = a.nextStep(board,state);
    }
    return temp;

}
