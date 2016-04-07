#include"systemmonitor.h"
SystemMonitor::SystemMonitor(QWidget *parent) :
    QWidget(parent)
{
    QTabWidget * tab = new QTabWidget;
    Info* info = new Info;
    ProcessTable* pt = new ProcessTable;
    tab->addTab(info,"Информация о системе");
    tab->addTab(pt,"Процессы");
    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(tab);
    this->setLayout(layout);
    this->show();
}
