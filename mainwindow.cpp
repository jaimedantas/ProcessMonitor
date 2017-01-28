#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <QTime>
#include <QTimer>
#include <QTimerEvent>
#include <stdlib.h>
#include <QTextStream>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    timeUp=10000;
    ui->setupUi(this);

//    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(chargeProcess()));
    timer->start(timeUp);

}

MainWindow::~MainWindow()
{
    delete ui;
    remove("comandPid.txt");
    remove("processColum.txt");
    remove("processColumFind.txt");
    remove("cpuUso.txt");
}

void MainWindow::killPid()
{
    if(isProcess(ui->lineEdit_PidProcess->text().toStdString()))
    {
        kill(ui->lineEdit_PidProcess->text().toInt(),SIGKILL);
        historicShow("Kill ");
    }
    else
    {
        historicShow("This process does not exists : ");
    }

    chargeProcess();

    searchProcess();
}

void MainWindow::stopPid()
{
    if(isProcess(ui->lineEdit_PidProcess->text().toStdString()))
    {
        historicShow("Stop ");
        kill(ui->lineEdit_PidProcess->text().toInt(),SIGSTOP);
    }
    else
    {
        historicShow("This process does not exists : ");
    }

    chargeProcess();

    searchProcess();
}

void MainWindow::continuePid()
{
    if(isProcess(ui->lineEdit_PidProcess->text().toStdString()))
    {
        historicShow("Continue ");
        kill(ui->lineEdit_PidProcess->text().toInt(),SIGCONT);
    }
    else
    {
        historicShow("This process does not exists : ");
    }

    chargeProcess();

    searchProcess();
}
QTextStream& qStdOut()
{
    static QTextStream ts( stdout );
    return ts;
}
void MainWindow::chargeProcess()
{
    ui->textBrowser_allProcess->clear();
    showProcess.clear();

    system("ps x -o pid,tty,time,command >processColum.txt");
    system("ps -A -o %cpu | awk '{s+=$1} END {print s}' >cpuUso.txt");
    ifstream arquivo, arquivo2;
    arquivo.open("processColum.txt");
    arquivo2.open("cpuUso.txt");
    while(arquivo.good())
    {
        string temporario;
        getline(arquivo, temporario );
        showProcess=showProcess +  temporario + "\n" ;
    }
    arquivo.close();

    while(arquivo2.good())
    {
        string linha;
        getline(arquivo2, linha);
        //showProcess=showProcess +  temporario + "\n" ;
        QString q = linha.c_str();
        QString vazio = "";

        //qDebug() <<"valor: "<<q;
        if(q!=vazio){
            float t = q.toFloat();
            int i = int(t + 0.5);
            qDebug() <<"n: "<<i;
            ui->progressBar->setValue(i);
            ui->labelCPU->setText(q+"%");
        }
    }
    arquivo2.close();
    getOnlyPid(showProcess);
    ui->textBrowser_allProcess->setText(processos.fromStdString(showProcess));
}

void MainWindow::chargefindProcess(string viewFind)
{
    ui->textBrowser_findProcess->clear();
    showProcess.clear();

    string gotoSystem;
    gotoSystem = viewFind + "> processColumFind.txt";
    system(gotoSystem.c_str());

    ifstream arquivo;
    arquivo.open("processColumFind.txt");
    while(arquivo.good())
    {
        string temporario;
        getline(arquivo, temporario );
        showProcess=showProcess +  temporario + "\n" ;
    }
    arquivo.close();

    ui->textBrowser_findProcess->setText(processos.fromStdString(showProcess));
}

void MainWindow::searchProcess()
{
    string searchString;
    if(ui->lineEdit_FindProcess->text().toStdString().size() == 0)
    {
    }
    else
    {
        searchString="ps aux | grep " + ui->lineEdit_FindProcess->text().toStdString();
        chargefindProcess(searchString);
    }
}

void MainWindow::timeUpdate()
{
    timeUp=1000*ui->lineEdit_TimeUpdating->text().toInt();
    timer->start(timeUp);
}

bool MainWindow::isProcess(string teste)
{

    if(atoi(teste.c_str())==0)
        return 0;
    else
        return 1;

}

void MainWindow::getOnlyPid(string teste)
{
    int flag=0;

            for(int aux=28; aux<=teste.size() ; aux++)
            {
                if( ( flag==0 ) & ( teste[aux] !=' ' ) )
                {
                    PID = PID + teste[aux] ;
                }
                else if(teste[aux] ==' ')
                {
                    flag++;
                }
                else if(teste[aux] == '\n' )
                {
                    flag=0;
                    PID=PID + "\n";
                }
            }
}

void MainWindow::historicShow(string comand)
{
    historicProcess= historicProcess + comand ;
    historicProcess= historicProcess + ui->lineEdit_PidProcess->text().toStdString() ;
    historicProcess= historicProcess + "\n";
    ui->textBrowser_stopedProcess->setText(saida.fromStdString(historicProcess));

}

