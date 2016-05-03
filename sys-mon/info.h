#ifndef INFO_H
#define INFO_H

#include"QLabel"
#include"QLayout"
#include"QProgressBar"
#include "QWidget"
#include "QtGui"
#include "iostream"
#include "fstream"
#include "pwd.h"    //для заполнения
#include "unistd.h" //имени пользователя
#include "sys/sysinfo.h"
#include "vector"
using namespace std;
class Info : public QWidget
{
    Q_OBJECT
public:
    explicit Info(QWidget *parent = 0);
private:
    QLabel * kernel;
    QLabel * hostname;
    QLabel * user;
    QLabel * uptime;
    QLabel * proc;
    QLabel * freq;
    QLabel * cpuload;
    QLabel * RAM;
    QLabel * RAMload;
    QProgressBar * cpubar;
    QProgressBar * RAMbar;
    QVBoxLayout * layout;
    QHBoxLayout * hlayout;
    vector<float> readCpuStats();
    int getCpuLoad(double dt);
public slots:
    void getInfo();
};

#endif // INFO_H
