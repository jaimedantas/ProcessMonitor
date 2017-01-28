#ifndef PROCESSOS_H
#define PROCESSOS_H

#include <QWidget>

namespace Ui
{
class processos;
}
class processos : public QWidget
{
    Q_OBJECT
public:
    explicit processos(QWidget *parent = 0);
    
signals:

private:
    Ui::processos *ui;
public slots:
    processos();
    ~processos();
    
};

#endif // PROCESSOS_H
