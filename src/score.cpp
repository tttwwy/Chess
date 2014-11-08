#include "score.h"

Score::Score(QWidget *parent) :
    QDialog(parent)
{

    if (!FileRead())
    {
        Int();
    }

    setupUi(this);
    SetShow();
}

Score::~Score()
{
    FileWrite();
}

void Score::on_pushButton_clicked()
{
    Int();
    SetShow();
    FileWrite();
    update();
}

void Score::is_win(bool iswin)
{
    if (winnum+losenum == 0)
    {
        isconwin = iswin;
    }
    if (iswin)
    {
        winnum++;
        if (isconwin)
        {
            connow++;
            if (connow > conwin)
                conwin = connow;
        }
        else
        {
            isconwin = false;
            connow = 0;
        }
    }
    else
    {
        losenum++;
        if (!isconwin)
        {
            connow++;
            if (connow > conlose)
                conlose  = connow;
        }
        else
        {
            isconwin = true;
            connow = 0;
        }
    }
    SetShow();
}

bool Score::FileWrite()
{
    QFile file("score.dat");
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QDataStream out(&file);
    out << quint32(0x12275478) << winnum << losenum << conwin << conlose << connow << isconwin;
    return true;
}

bool Score::FileRead()
{
    QFile file("score.dat");
    if (!file.open(QIODevice::ReadOnly))
        return false;
    QDataStream in(&file);
    quint32 flag;
    in >> flag;
    if (flag != quint32(0x12275478))
        return false;
    in >> winnum >> losenum >> conwin >> conlose >> connow >> isconwin;
    return true;

}

void Score::SetShow()
{
    label_2->setText("已玩游戏："+QString::number(winnum+losenum));
    label->setText("已胜游戏："+QString::number(winnum));
    if (winnum+losenum != 0)
    label_3->setText("获胜率："+QString::number(winnum*100/(winnum+losenum))+"%");
    else
        label_3->setText("获胜率:0%");

    label_4->setText("最多连胜："+QString::number(conwin));
    label_5->setText("最多连败："+QString::number(conlose));
    label_6->setText("当前连局："+QString::number(connow));
    update();
}

void Score::Int()
{
    winnum = 0;
    losenum = 0;
    conwin = 0;
    conlose = 0;
    connow = 0;
    isconwin = true;
}
