#ifndef SYSMON_H
#define SYSMON_H

#include "QtGui"
#include "info.h"
#include "table.h"
class SystemMonitor : public QWidget
{
    Q_OBJECT
public:
    explicit SystemMonitor(QWidget *parent = 0);
};

#endif // SYSTEMMONITOR_H
