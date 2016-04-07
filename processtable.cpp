#include "processtable.h"
ProcessTable::ProcessTable(QWidget *parent) :
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
    update();

    layout->addWidget(table);
    layout->addLayout(hlayout);
    this->setLayout(layout);

    QTimer *timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(4000);
}
void ProcessTable::update()
{
    table->setColumnCount(2);
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
            QString icon = "/usr/share/icons/hicolor/32x32/apps/" + QString::fromStdString(s) + ".png";
            //QFile file(icon);
            table->insertRow(lastRow);
            table->setColumnWidth(0,150);

            /*if(!file.exists()) {
                icon = "icon.png";
            }*/
            table->setItem(lastRow,0,new QTableWidgetItem(QPixmap(icon),QString::fromStdString(s)));
            table->setItem(lastRow,1,new QTableWidgetItem(str));
        } else {
            continue;
        }
    }
}
void ProcessTable::kill()
{
    QList<QTableWidgetItem*> list = table->selectedItems();
    QTableWidgetItem* item = list.value(0);
    QString str = item->text();
    QProcess::execute("kill", QStringList() << str);
    update();
}
