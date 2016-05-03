#include "table.h"
Table::Table(QWidget *parent) :
QWidget(parent)
{
    hlayout = new QHBoxLayout;
    button = new QPushButton("Kill");
    button->setToolTip("Для завершения процесса вы должны выделить его PID и нажать на кнопку \"Завершить\"");
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
    table->setColumnCount(3);
    table->setRowCount(0);

    QStringList list;
    list << "Name" << "PID";
    table->setHorizontalHeaderLabels(list);
    QDir * dir = new QDir("/proc");
    list = dir->entryList(QStringList("*"),QDir::AllDirs);

    foreach(QString str, list) {
        if(str.toInt()) {
            ifstream stream;
            stream.open("/proc/" + str.toLatin1() + "/comm");
            string s; getline(stream,s);
            int lastRow = table->rowCount();

            table->insertRow(lastRow);
            table->setColumnWidth(0,100);

            table->setItem(lastRow,0,new QTableWidgetItem(QString::fromStdString(s)));
            table->setItem(lastRow,1,new QTableWidgetItem(str));
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
