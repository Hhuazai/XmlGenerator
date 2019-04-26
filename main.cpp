#include "XmlGenerator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XmlGenerator w;
    w.show();

    return a.exec();
}
