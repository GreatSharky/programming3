#include "city.h"

#include <memory>

#include <QApplication>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    std::shared_ptr<Aaro::City> tre = std::make_shared<Aaro::City>();

    return a.exec();
}
