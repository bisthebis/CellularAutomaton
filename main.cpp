#include <iostream>
#include "grid.h"
#include "gridwidget.h"
#include <random>

#include <QtWidgets>
#include <QApplication>
#include <QTimer>
#include <QTime>


using namespace std;


int main(int argc, char *argv[])
{
    Grid* GRID_PTR = new Grid(500, 500);
    Grid& grille = *GRID_PTR;

    QApplication app(argc, argv);
    GridWidget window;
    window.setGrid(&grille);
    window.show();




    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    auto gridRandomFiller = [&](Grid& grid, int x, int y) {
        grid.setNextValueAt(x, y, dis(gen));


    };



    //QObject::connect(&grille, &Grid::hasChanged, &window, &GridWidget::update);




    QTimer timer;
    timer.setInterval(500);
    QObject::connect(&timer, &QTimer::timeout, &grille, &Grid::GameOfLifeStep);
    timer.start();


    QPixmap exported_map(500, 500);
    QObject::connect(&grille, &Grid::hasChanged, [&](){grille.paint(&exported_map);});

    QObject::connect(qApp, &QApplication::aboutToQuit, [&](){cout << "Leaving ! " << endl; exported_map.save("Grid_export.png", "PNG");});


/*    auto gridRegularFiller = [](Grid& grid, int x, int y) {
        grid.setNextValueAt(x, y, (x+1)*10 + (y+1));


    };




    auto gridIncrement = [](Grid& grid, int x, int y) {
        grid.setNextValueAt(x, y, grid.getValueAt(x, y)+1);


    };*/

    auto gridNullFiller = [](Grid& grid, int x, int y) {
        grid.setNextValueAt(x, y, 0);
    };

    grille.fill(gridNullFiller);
    grille.setNextValueAt(1, 0, 1);
    grille.setNextValueAt(2, 1, 1);
    grille.setNextValueAt(0, 2, 1);
    grille.setNextValueAt(1, 2, 1);
    grille.setNextValueAt(2, 2, 1);
    grille.update();

    grille.fill(gridRandomFiller);





    return app.exec();
}
