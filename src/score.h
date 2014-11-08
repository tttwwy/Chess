#ifndef SCORE_H
#define SCORE_H

#include "ui_score.h"
#include <QFile>

class Score : public QDialog, private Ui::Score
{
    Q_OBJECT
    
public:
    explicit Score(QWidget *parent = 0);
    ~Score();
    void SetShow();
    void Int();
private slots:
    void on_pushButton_clicked();
    void is_win(bool iswin);

private:
    int winnum;
    int losenum;
    int conwin;
    int conlose;
    int connow;
    bool isconwin;
    bool FileRead();
    bool FileWrite();

signals:


};

#endif // SCORE_H
