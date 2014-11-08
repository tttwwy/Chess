#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include "config.h"
#include <QSound>

#include "score.h"


class MainWindow : public QMainWindow,public Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    config *Config;
    Score *information;
    void showConfig();
    void MusicOn();
    void MusicOff();
private:
    QSound * bells;






    ~MainWindow();


private slots:

    void on_set_triggered();

    void on_redo_triggered();
    void on_newGame_triggered();
    void on_stop_triggered();
    void on_undo_triggered();
    void on_about_triggered();
    void on_help_triggered();


    void on_OpenFile_triggered();
    void on_SaveFile_triggered();
    void on_action_triggered();
    void on_information_triggered();
    void on_hint_triggered();
};

#endif // MAINWINDOW_H
