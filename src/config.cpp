#include "config.h"
#include "ui_config.h"

config::config(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::config)
{
    playerSheep = 0;
    playerWolf = 0;
    hardness  = 0;
    ui->setupUi(this);
}

void config::setConfig()
{
    ui->sheep->setCurrentIndex(playerSheep);
    ui->wolf->setCurrentIndex(playerWolf);
    ui->hardness->setCurrentIndex(hardness);
}

void config::setVale(int wolf, int sheep, int hard)
{
    playerSheep = sheep;
    playerWolf = wolf;
    hardness = hard;
}



config::~config()
{
    delete ui;

}


void config::on_pushButton_clicked()
{
    playerWolf = ui->wolf->currentIndex();
    playerSheep = ui->sheep->currentIndex();
    hardness = ui->hardness->currentIndex();
    emit configChange(playerWolf,playerSheep,hardness);
    close();
}



void config::on_pushButton_2_clicked()
{
    setConfig();
    close();
}

bool config::IsComputer()
{
    if (playerSheep != 0 || playerWolf != 0 )
        return true;
    return false;
}
