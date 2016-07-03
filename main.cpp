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

    Grid* GRID_PTR = new Grid(500, 500);
    Grid& grille = *GRID_PTR;


    MyWindow window;
    window.show();

    auto gridRandomBinaryFiller = [&](Grid& grid, int x, int y) {
        grid.setNextValueAt(x, y, qrand()%2);


    };
    grille.fill(gridRandomBinaryFiller);



    /*QPixmap exported_map(500, 500);
    QObject::connect(&grille, &Grid::hasChanged, [&](){grille.paint(&exported_map);});

    QObject::connect(qApp, &QApplication::aboutToQuit, [&](){cout << "Leaving ! " << endl; exported_map.save("Grid_export.png", "PNG");});*/






    return app.exec();
}
