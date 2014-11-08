#ifndef DEFINE_H
#define DEFINE_H


#define sheep 1
#define wolf 2
#define gridNum 5
#define wolfNum 3
#define sheepNum 15
typedef unsigned char byte;

#include <QPoint>

struct step
{
    QPoint start;
    byte startVal;
    QPoint end;
    byte endVal;
};

struct ChessMove{
    byte ChessID;
    QPoint start;
    QPoint end;
    int score;
};
#endif // DEFINE_H
