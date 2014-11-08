#include "chessboard.h"

chessboard::chessboard(QWidget *parent) :
    QWidget(parent)
{
    startflag = 0;
    state = wolf;
    gridSize = 70;
    chessBoard_Init();
    player[0] = player[1] = player[2]= 0;
    hardness = 0;
    m_pSE = new CNegamaxEngine;
    pMG = new CMoveGenerator;
    pEvel = new CEveluation;

    m_pSE->SetSearchDeepth(2);
    m_pSE->SetMoveGenerator(pMG);
    m_pSE->SetEveluator(pEvel);

}

void chessboard::setstartflag(int flag)
{
    if (flag > 0)
        flag = 1;
    if (flag < 0)
        flag = 0;
    startflag = flag;
}


void chessboard::chessBoard_Init()
{
    int row,line;
    for (row = 0;row < gridNum;row++)
        for (line = 0;line < gridNum;line++)
            board[row][line] = 0;
    for (row = 0;row < 3;row++)
        for (line = 0;line < gridNum;line++)
            board[row][line] = sheep;
    board[4][1] =  board[4][2] = board[4][3] = wolf;
    state = wolf;
    start = QPoint(-1,-1);

    startflag = 0;

    setMousestate();
    undo.clear();
    redo.clear();
    update();
}

void chessboard::nextStep()
{

    int result = isOver();
    if (result)
        gameOver(result);

    else
    {
        state = state ^ 3;
        if (state == wolf)
            qDebug("%d",pEvel->Eveluate(board,true));
        else
            qDebug("%d",pEvel->Eveluate(board,false));
        qDebug("Sheep:%d  Wolf:%d",pEvel->sheepscore,pEvel->wolfscore);

        setMousestate();
        if (player[state] == 1)
        {
            computerMove();
            nextStep();
        }

    }

}

void chessboard::setMousestate()
{
    if (player[state] == 0)
        mousestate = 1;
    else
        mousestate = 0;
}

void chessboard::move(QPoint start, QPoint end)
{
    this->start = start;
    this->end = end;
    saveStep();
    board[end.x()][end.y()] =  board[start.x()][start.y()];
    board[start.x()][start.y()] = 0;

    update();

}

int chessboard::getStartflag(){
    return startflag;
}



void chessboard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawBoard(painter);
    drawChess(painter);
    if (start.x()>=0)
    {
        if (mousestate == 3)
            drawSquare(painter,start,Qt::red);
        if (mousestate == 1)
        {
            drawSquare(painter,start,Qt::red);
            drawSquare(painter,end,Qt::red);
        }
    }
}



void chessboard::drawBoard(QPainter &painter)
{
    painter.setPen(Qt::black);
    for(int i = 0, j = 0; i <= gridNum; i++, j++)
    {
        painter.drawLine(0, i*gridSize, gridNum*gridSize, i*gridSize);
        painter.drawLine(j*gridSize, 0, j*gridSize, gridNum*gridSize);
    }
}




void chessboard::drawChess(QPainter &painter)
{
    QPixmap pixsheep;
    pixsheep.load(":/ico/image/sheep.png");
    QPixmap pixwolf;
    pixwolf.load(":/ico/image/wolf.png");

    for (int i = 0;i < gridNum;i++)
        for (int j = 0;j < gridNum;j++)
        {
            if (board[i][j] == sheep)
            {
                painter.drawPixmap(j*gridSize+2,i*gridSize+2,gridSize-2,gridSize-2,pixsheep);
            }
            if (board[i][j] == wolf)
            {
                painter.drawPixmap(j*gridSize+2,i*gridSize+2,gridSize-2,gridSize-2,pixwolf);
            }
        }
}

void chessboard::drawSquare(QPainter &painter,QPoint point,Qt::GlobalColor style)
{
    painter.setPen(style);
    painter.drawRect(point.y()*gridSize+1,point.x()*gridSize+1,gridSize-2,gridSize-2);
}


void chessboard::mousePressEvent(QMouseEvent *event)
{
    if (startflag == 0 || mousestate == 0)
        return;
    if(event->button() == Qt::LeftButton){
        int x = event->y()/gridSize;
        int y = event->x()/gridSize;

        if (x >= 0 && x <gridSize && y >= 0 && y < gridSize)
        {

            if ( (mousestate == 1 || mousestate == 2) && board[x][y] == state)
            {
                start = QPoint(x,y);
                mousestate = 3;
                update();
            }
            else if (mousestate == 3)
            {
                if (board[x][y] == state)
                {
                    start = QPoint(x,y);
                    mousestate = 3;
                    update();
                }
                else
                {
                    if (checkboard(x,y))
                    {
                        end = QPoint(x,y);

                        move(start,end);
                        nextStep();
                    }
                    else
                    {
                        mousestate = 3;
                    }
                }
            }
        }
    }
}
bool chessboard::checkboard(int endx,int endy)
{
    QPoint end(endx,endy);

    int dis1[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    int dis2[4][2] = {{0,2},{0,-2},{2,0},{-2,0}};
    if (state == wolf)
    {
        for (int i = 0;i < 4;i++)
        {
            if (start.x()+ dis1[i][0] == end.x() && start.y() + dis1[i][1]==end.y())
            {
                if (board[end.x()][end.y()]== 0)
                    return true;
                if (board[end.x()][end.y()]== sheep)
                    return false;
            }
        }
        for (int i = 0;i < 4;i++)
        {
            if (start.x()+ dis2[i][0] == end.x() && start.y() + dis2[i][1]==end.y())
            {
                if (board[end.x()][end.y()]== 0)
                    return false;
                if (board[end.x()][end.y()]== sheep)
                {
                    if(board[start.x()+dis1[i][0]][start.y()+dis1[i][1]] == 0)
                        return true;
                    else
                        return false;
                }
            }
        }

    }

    if (state == sheep)
    {
        for (int i = 0;i < 4;i++)
        {
            if (start.x()+ dis1[i][0] == end.x() && start.y() + dis1[i][1] == end.y())
            {
                if (board[end.x()][end.y()]== 0)
                    return true;
            }
        }

    }
    return false;
}

void chessboard::saveStep()
{
    step temp;
    temp.start = start;
    temp.end = end;
    temp.startVal = board[start.x()][start.y()];
    temp.endVal = board[end.x()][end.y()];
    undo.push(temp);
    if (player[wolf] != 1 || (player[wolf] == 1 && undo.size() != 1))
        emit isundo(true);
}

bool chessboard::restoreStep(bool direction)
{
    bool flag = false;
    if (startflag == 1)
    {
        step temp;
        if (direction)
        {
            if (!undo.empty())
            {

                flag = true;
                temp = undo.top();
                temp.startVal = board[temp.start.x()][temp.start.y()];
                temp.endVal = board[temp.end.x()][temp.end.y()];
                redo.push(temp);
                temp = undo.top();
                undo.pop();
                board[temp.start.x()][temp.start.y()] = temp.startVal;
                board[temp.end.x()][temp.end.y()] = temp.endVal;
                emit isredo(true);
                state = state ^ 3;
            }
        }
        else
        {
            if (!redo.empty())
            {
                flag = true;
                temp = redo.top();
                temp.startVal = board[temp.start.x()][temp.start.y()];
                temp.endVal = board[temp.end.x()][temp.end.y()];
                undo.push(temp);
                temp = redo.top();
                redo.pop();
                board[temp.start.x()][temp.start.y()] = temp.startVal;
                board[temp.end.x()][temp.end.y()] = temp.endVal;
                emit isundo(true);
                state = state ^ 3;
            }
        }

        if(redo.empty())
            emit isredo(false);

        if ( (player[wolf] == 1 && undo.size() == 1) || undo.empty())
            emit isundo(false);

        update();

    }
    return flag;
}
bool chessboard::fileRead()
{
    QString path = QFileDialog::getOpenFileName(this, tr("打开棋谱"), ".", tr("棋谱文件(*.sgf)"));
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    QDataStream in(&file);

    quint32 flag;
    in >> flag;
    step temp;
    if (flag == quint32(0x12375478))
    {
        chessBoard_Init();
        startflag = 1;
        player[0] = player[1] = player[2]= 0;
        emit isundo(false);
        emit isredo(true);
        while(!file.atEnd())
        {
            in >> temp.start >> temp.end >> temp.startVal >> temp.endVal;
            redo.push(temp);
        }
    }
    return true;
}

bool chessboard::fileWrite()
{
    QString path = QFileDialog::getSaveFileName(this, tr("保存棋谱"), ".", tr("棋谱文件(*.sgf)"));
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
        return false;
    QDataStream out(&file);
    out << quint32(0x12375478);
    QStack<step> write = undo;
    step temp;
    byte position[gridNum][gridNum];
    for (int i = 0;i < gridNum;i++)
        for (int j = 0;j < gridNum;j++)
        {
            position[i][j] = board[i][j];
        }


    while(!write.empty())
    {
        temp = write.top();
        out << temp.start << temp.end << position[temp.start.x()][temp.start.y()] << position[temp.end.x()][temp.end.y()];

        write.pop();
        position[temp.start.x()][temp.start.y()] = temp.startVal;
        position[temp.end.x()][temp.end.y()] = temp.endVal;

    }

    return true;

}

int chessboard::undoSize()
{
    return undo.size();
}

int chessboard::isOver()
{
    bool WolfLive = false,SheepLive = false;
    int SheepNum = 0;

    int dis[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};


    for (int i = 0;i<gridNum;i++)
        for (int j = 0;j<gridNum;j++)
        {
            if (board[i][j] == wolf)
            {
                for (int k = 0;k < 4;k++)
                {
                    if (i+dis[k][0] >=0
                            && i + dis[k][0] < gridNum
                            && j + dis[k][1] >= 0
                            && j + dis[k][1] < gridNum
                            && board[i+dis[k][0]][j+dis[k][1]] == 0)
                    {

                        WolfLive = true;
                        break;
                    }
                }
            }
            if (board[i][j] == sheep)
            {
                SheepNum++;
            }
        }

    if (SheepNum >= 3)
        SheepLive = true;

    if (state == sheep && WolfLive == false)
        return sheep;
    if (state == wolf && SheepLive == false)
        return wolf;
    return 0;
}

void chessboard::gameOver(int result)
{
    if (result == wolf)
    {
        if (player[wolf] == 0)
            emit winner(true);
        else
            emit winner(false);
        QMessageBox::information(this, tr("狼胜!"),tr("狼胜！\n""羊已经回天乏术啦"));
    }
    else if (result == sheep)
    {
        if (player[sheep] == 0)
            emit winner(true);
        else
            emit winner(false);
        QMessageBox::information(this, tr("羊胜!"),tr("羊胜！\n""狼已经无路可走啦！"));

    }
}

void chessboard::gameStart()
{
    chessBoard_Init();
    setstartflag(1);
    update();


    setMousestate();
    if (mousestate == 0 && startflag == 1)
    {
        computerMove();
        nextStep();
    }

}

void chessboard::computerMove()
{
    repaint();

    if (state == wolf)
    {
        m_pSE->SearchAGoodMove(board,true);
    }
    if (state == sheep)
    {
        m_pSE->SearchAGoodMove(board,false);
    }

    move(m_pSE->m_cmBestMove.start,m_pSE->m_cmBestMove.end);
}

void chessboard::mouseMoveEvent(QMouseEvent *event)
{
}



void chessboard::mouseReleaseEvent(QMouseEvent *event)
{

}



void chessboard::setConfig(int playerWolf, int playerSheep, int hardness)
{
    player[wolf] = playerWolf;
    player[sheep] = playerSheep;
    this->hardness = hardness;
    m_pSE->SetSearchDeepth(hardness+1);
    setMousestate();
    if (mousestate == 0 && startflag == 1)
    {
        computerMove();
        nextStep();
    }
}

void chessboard::help()
{
    if (state == wolf)
    {
        m_pSE->SearchAGoodMove(board,true);
    }
    if (state == sheep)
    {
        m_pSE->SearchAGoodMove(board,false);
    }

    start = m_pSE->m_cmBestMove.start;
    end = m_pSE->m_cmBestMove.end;
    update();
}






