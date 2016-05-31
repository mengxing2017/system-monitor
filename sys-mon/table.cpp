#include "table.h"
Table::Table(QWidget *parent) :
QWidget(parent)
{
    hlayout = new QHBoxLayout;
    button = new QPushButton("Kill");
    button->setToolTip("Для завершения процесса вы должны выделить его PID и нажать на кнопку \"Kill\"");
    connect(button,SIGNAL(clicked()),this,SLOT(kill()));

    hlayout->addStretch();
    hlayout->addWidget(button);
    layout = new QVBoxLayout;
    table = new QTableWidget;

    getInfo();

    layout->addWidget(table);
    layout->addLayout(hlayout);
    this->setLayout(layout);
    warning = new QLabel;
    warning -> setText("ID");

    QTimer *timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(getInfo()));
    timer->start(4000);
}

void Table::getInfo()
{
    table->setColumnCount(4);
    table->setRowCount(0);

    QStringList list;
    list << "Name" << "PID" << "Mem(pg)" << "Status";
    table->setHorizontalHeaderLabels(list);
    QDir * dir = new QDir("/proc");
    list = dir->entryList(QStringList("*"),QDir::AllDirs);

    foreach(QString str, list) {
        if(str.toInt()) {
            ifstream stream;
            stream.open("/proc/" + str.toLatin1() + "/comm");
            string s; getline(stream,s);
            stream.close();
            stream.open("/proc/" + str.toLatin1() + "/status");
            string stat;
            stream>>stat;stream>>stat;stream>>stat;stream>>stat;
            stream.close();
            stream.open("/proc/" + str.toLatin1() + "/statm");
            string mem;
            stream>>mem;
            int n = atoi(mem.c_str());

            QString memm = QString::number(n);

            int lastRow = table->rowCount();

            QString icon = "/usr/share/icons/hicolor/32x32/apps/" + QString::fromStdString(s) + ".png";
            QFile file(icon);
            if(!file.exists()) {
                icon = "/home/tmoha/github/system-monitor/sys-mon/binary.jpg";
            }

            table->insertRow(lastRow);
            table->setColumnWidth(0,100);

            table->setItem(lastRow,0,new QTableWidgetItem(QPixmap(icon),QString::fromStdString(s)));
            table->setItem(lastRow,1,new QTableWidgetItem(str));
            table->setItem(lastRow,2,new QTableWidgetItem(memm));
            table->setItem(lastRow,3,new QTableWidgetItem(QString::fromStdString(stat)));

        } else
        {
            continue;
        }
    }
}

void Table::kill()
{
    QList<QTableWidgetItem*> list = table->selectedItems();
    QTableWidgetItem* item = list.value(0);
    QString str = item->text();
    QProcess::execute("kill", QStringList() << str);
    getInfo();
}
