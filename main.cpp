#include <iostream>
#include "grid.h"
#include <random>


using namespace std;

int main(int argc, char *argv[])
{
    Grid grille(10, 10);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    auto gridRegularFiller = [](Grid& grid, int x, int y) {
        grid.setNextValueAt(x, y, (x+1)*10 + (y+1));


    };

    auto gridNullFiller = [](Grid& grid, int x, int y) {
        grid.setNextValueAt(x, y, 0);
    };

    auto gridRandomFiller = [&](Grid& grid, int x, int y) {
        grid.setNextValueAt(x, y, dis(gen));


    };

    auto gridIncrement = [](Grid& grid, int x, int y) {
        grid.setNextValueAt(x, y, grid.getValueAt(x, y)+1);


    };

    auto gridGameOfLifeStep = [](Grid& grid, int x, int y) { //Requires every cell to be either 0 or 1 !
        int numberOfNeigborsAlive = grid.getValueAt(x-1, y-1) +
                                    grid.getValueAt(x, y-1) +
                                    grid.getValueAt(x+1, y-1) +
                                    grid.getValueAt(x-1, y) +
                                    grid.getValueAt(x+1, y) +
                                    grid.getValueAt(x-1, y+1) +
                                    grid.getValueAt(x, y+1) +
                                    grid.getValueAt(x+1, y+1);



        if ( (numberOfNeigborsAlive == 3) || ( (grid.getValueAt(x, y) == 1) && (numberOfNeigborsAlive == 2) ) )
            grid.setNextValueAt(x, y, 1);
        else
            grid.setNextValueAt(x, y, 0);

    };

    grille.fill(gridNullFiller);
    grille.setNextValueAt(1, 0, 1);
    grille.setNextValueAt(2, 1, 1);
    grille.setNextValueAt(0, 2, 1);
    grille.setNextValueAt(1, 2, 1);
    grille.setNextValueAt(2, 2, 1);
    grille.update();
    grille.print();

    for (int i = 0; i < 5; ++i)
    {
        grille.fill(gridGameOfLifeStep);
        grille.print();
    }



    return 0;
}
