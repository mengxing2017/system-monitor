#include "info.h"
#include "QString"
Info::Info(QWidget *parent) :
    QWidget(parent)
{
    hostname   = new QLabel("Hostname: ");
    user       = new QLabel("User: ");
    uptime     = new QLabel("Uptime: ");
    proc       = new QLabel("Processor: ");
    freq       = new QLabel("Frequency: ");
    cpuload    = new QLabel("CPU load: ");
    mem        = new QLabel("Total RAM: ");
    memload    = new QLabel("Usage RAM: ");
    cpubar     = new QProgressBar;
    membar     = new QProgressBar;
    layout     = new QVBoxLayout;
    hlayout    = new QHBoxLayout;

    cpubar->setMaximumHeight(21); membar->setMaximumHeight(21);
    hlayout->addWidget(cpuload); hlayout->addWidget(cpubar);
    layout->addWidget(hostname); layout->addWidget(user);
    layout->addWidget(uptime); layout->addWidget(proc);
    layout->addWidget(freq); layout->addLayout(hlayout);
    layout->addWidget(mem); layout->addWidget(memload);
    layout->addWidget(membar); setLayout(layout);

    update();

    QTimer *timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(2000);
}
void Info::update()
{
    ifstream stream("/proc/sys/kernel/hostname");
    string str;
    getline(stream,str);
    hostname->setText("Hostname: " + QString::fromStdString(str));

    uid_t uid = geteuid();
    passwd *pw = getpwuid(uid);
    user->setText("User: " + QString::fromStdString(pw->pw_name));

    struct sysinfo o;
    sysinfo(&o);
    long up = o.uptime;
    int hour = up/60/60;
    int min = (up - hour*60*60) / 60;
    int sec =  ((up - hour*60*60) - min*60);
    QString e = QString::number(hour) +  QString(" h. ") + QString::number(min) + QString(" m. ")
                + QString::number(sec) + QString(" s.");
    uptime->setText("Uptime: " + e);

    stream.close(); stream.open("/proc/cpuinfo");
    for(int i = 0; i < 16;i++)
        stream >> str;
    getline(stream,str);
    proc->setText("Processor: " + QString::fromStdString(str));
    for(int i = 0; i< 10; i++)
        stream >> str;
    freq->setText("Frequency: " + QString::fromStdString(str) + " MHz");

    cpubar->setValue(getCpuLoad(0.3));
    stream.close();

    stream.open("/proc/meminfo");
    stream >> str; stream >> str;
    int totalMemory = atoi(str.c_str());

    int gb = (totalMemory / 1024) / 1024;
    int mb = (totalMemory - gb * 1024 * 1024) / 1024;

    if (gb > 0)
       e = QString::number(gb) + QString(" Gb ");
    else
       e = QString("");
    if (mb > 0)
       e += QString::number(mb) + QString(" Mb ");

    mem->setText("Total RAM: " + e);

    int freeMemory = 0;
    for (int i = 0 ; i < 3 ; i++)
    {
        stream >> str; stream >> str;
        freeMemory += atoi(str.c_str());
    }

    int usedMemory = totalMemory - freeMemory;
    gb = usedMemory / 1024 / 1024;
    mb = (usedMemory - gb * 1024 * 1024) / 1024;

    if (gb > 0)
    {
       e = QString::number(gb) + QString(" Gb ") + QString::number(mb)+ QString(" Mb ");
    }
    else
    {
       e = QString::number(mb) + QString(" Mb ");
    }
    memload->setText("Usage RAM: " + e);
    int usageRAM = (usedMemory * 100) / totalMemory;
    membar -> setValue(usageRAM);
}
int Info::getCpuLoad(double dt)
{
    vector<float> stats1 = readCpuStats();
    QProcess::execute("sleep",QStringList() << QString::number(dt));
    vector<float> stats2 = readCpuStats();
    int size1 = stats1.size();
    int size2 = stats2.size();
    if (!size1 || !size2 || size1 != size2) return 2;
    for (int i = 0; i < size1; ++i)
        stats2[i] -= stats1[i];
    int sum = 1;
    for (int i = 0; i < size1; ++i)
        sum += stats2[i];
    int load = 100 - (stats2[size2 - 1] * 100 / sum);
    return load;
}
vector<float> Info::readCpuStats()
{
    vector<float> ret;
    ifstream stat_file("/proc/stat");
    if (!stat_file.is_open())
    {
        cout << "Unable to open /proc/stat" << std::endl;
        return ret;
    }
    int val;
    string tmp;
    stat_file >> tmp;
    for (int i = 0; i < 4; ++i)
    {
        stat_file >> val;
        ret.push_back(val);
    }
    stat_file.close();
    return ret;
}
