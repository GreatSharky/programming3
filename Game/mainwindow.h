#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphics/simplemainwindow.hh"
#include "city.h"
#include "offlinereader.hh"

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <memory>

QString const BUSFILE = ":/offlinedata/offlinedata/final_bus_liteN.json";
QString const STOPFILE = ":/offlinedata/offlinedata/full_stations_kkj3.json";

namespace Aaro {
/**
 * @brief The MainWindow class
 * Window where the game is played
 */
class MainWindow : public CourseSide::SimpleMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

private:
    bool addInformation();

    std::unique_ptr<City> tre;
    //City tre;
    std::shared_ptr<CourseSide::OfflineData> data_;
    bool dataread_;
};

}

#endif // MAINWINDOW_H
