#include <QtGui/QApplication>
#include "gui/Enter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // It's used for QSettings
    a.setApplicationName("unnamed");
    a.setOrganizationName("unnamed");

    Enter w;
    w.show();

    return a.exec();
}
