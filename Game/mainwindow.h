#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphics/simplemainwindow.hh"
#include "city.h"

#include <QObject>
#include <QWidget>
#include <memory>

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

};

}

#endif // MAINWINDOW_H
