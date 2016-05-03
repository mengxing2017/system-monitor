#include"sysmon.h"

SystemMonitor::SystemMonitor(QWidget *parent) :
    QWidget(parent)
{
    QTabWidget * tab = new QTabWidget;
    Info* info = new Info;
    Table* pt = new Table;

    tab->addTab(info,"Info");
    tab->addTab(pt,"Processes");

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(tab);
    this->setLayout(layout);
    this->show();
}
