#ifndef Table_H
#define Table_H

#include "QWidget"
#include"QLayout"
#include"QTableWidget"
#include"QPushButton"
#include "QtGui"
#include "iostream"
#include "fstream"
using namespace std;
class Table : public QWidget
{
    Q_OBJECT
public:
    explicit Table(QWidget *parent = 0);
private:
    QTableWidget * table;
    QHBoxLayout * hlayout;
    QPushButton * button;
    QVBoxLayout * layout;
public slots:
    void getInfo();
    void kill();
};

#endif // Table_H
