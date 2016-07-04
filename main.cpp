#include <iostream>
#include "grid.h"
#include "gridwidget.h"
#include <random>

#include <QtWidgets>
#include <QApplication>
#include <QTime>

#include "mywindow.h"

using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qsrand(QTime::currentTime().msec());

    MyWindow window;
    window.show();

    return app.exec();
}
