#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include<string>
#include <cstring>
#include <iostream>
#include <QString>
#include <qstring.h>
#include <QTime>
#include <QTimer>
#include <QTimerEvent>


using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    

private:
    Ui::MainWindow *ui;
    QTimer *timer=new QTimer(this);
    QString saida, processos;
    string historicProcess, showProcess, PID;
    int timeUp=1000;
    void historicShow(string comand);

private slots:
    void killPid();
    void stopPid();
    void continuePid();
    void chargeProcess();
    void chargefindProcess(string viewFind);
    void searchProcess();
    void timeUpdate();
    bool isProcess(string teste);
    void getOnlyPid(string teste);
};

#endif // MAINWINDOW_H
