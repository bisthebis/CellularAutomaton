#include <iostream>
#include "grid.h"
#include "gameoflifepixmap.h"
#include <random>

#include <QtWidgets>
#include <QApplication>
#include <QTimer>
#include <QTime>


using namespace std;

#include "mywindow.h"

int main(int argc, char *argv[])
{
    Grid grille(250, 250);

    QApplication app(argc, argv);
    MyWindow window(nullptr, &grille);


    window.show();




    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    auto gridRandomFiller = [&](Grid& grid, int x, int y) {
        grid.setNextValueAt(x, y, dis(gen));


    };



    QObject::connect(&grille, SIGNAL(hasChanged(Grid*)), &window, SLOT(updateLabel()));

    QPushButton button("Step", &window);
    button.show();

    QObject::connect(&button, SIGNAL(clicked(bool)), &grille, SLOT(GameOfLifeStep()));


    QTimer timer;
    timer.setInterval(500);
    QObject::connect(&timer, SIGNAL(timeout()), &grille, SLOT(GameOfLifeStep()));
    timer.start();




/*    auto gridRegularFiller = [](Grid& grid, int x, int y) {
        grid.setNextValueAt(x, y, (x+1)*10 + (y+1));


    };

    auto gridNullFiller = [](Grid& grid, int x, int y) {
        grid.setNextValueAt(x, y, 0);
    };


    auto gridIncrement = [](Grid& grid, int x, int y) {
        grid.setNextValueAt(x, y, grid.getValueAt(x, y)+1);


    };*/



    /*grille.fill(gridNullFiller);
    grille.setNextValueAt(1, 0, 1);
    grille.setNextValueAt(2, 1, 1);
    grille.setNextValueAt(0, 2, 1);
    grille.setNextValueAt(1, 2, 1);
    grille.setNextValueAt(2, 2, 1);
    grille.update();*/

    grille.fill(gridRandomFiller);





    return app.exec();
}
