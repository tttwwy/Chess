#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>

namespace Ui {
class config;
}

class config : public QDialog
{
    Q_OBJECT

public:
    explicit config(QWidget *parent = 0);
//    void setConfig(int wolf,int sheep,int hardness);
    void setConfig();
    void setVale(int ,int ,int );
    ~config();
    bool IsComputer();
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
signals:
    void configChange(int,int,int);


private:
    Ui::config *ui;
    int playerSheep;
    int playerWolf;
    int hardness;

};

#endif // CONFIG_H
