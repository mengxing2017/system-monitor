#include "sysmon.h"
#include "QStyleFactory"
#include "QApplication"
int main(int argc,char** argv)
{
    QApplication app(argc,argv);
    QStyle * style = QStyleFactory::create("Cleanlooks");
    app.setStyle(style);
    SystemMonitor sys;
    return app.exec();
}
