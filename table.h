#ifndef ProcTable_H
#define ProcTable_H

#include "QWidget"
#include"QLayout"
#include"QTableWidget"
#include"QPushButton"
#include "QtGui"
#include "iostream"
#include "fstream"
using namespace std;
class ProcTable : public QWidget
{
    Q_OBJECT
public:
    explicit ProcTable(QWidget *parent = 0);
private:
    QTableWidget * table;
    QHBoxLayout * hlayout;
    QPushButton * button;
    QVBoxLayout * layout;
public slots:
    void getInfo();
    void kill();
};

#endif // ProcTable_H
