#include "grid.h"

#include <iostream>

#include <QPainter>

Grid::Grid(CoordType width, CoordType height, char outOfBoundsValue, QObject* parent) :
    QObject(parent),
    outOfBoundsValue(outOfBoundsValue),
    width(width),
    height(height),
    current(width*height, 0),
    next(current) //Copy of current
{
}


char Grid::getValueAt(CoordType x, CoordType y) const
{
    if(x >= width || y >= height || x < 0 || y < 0)
        return outOfBoundsValue;

    return current[x + y * width];
}
void Grid::setNextValueAt(CoordType x, CoordType y, char value)
{
    if(x >= width || y >= height || x < 0 || y < 0)
        return; //Can't modify unexisting cells !

    next[x + y * width] = value;
}

void Grid::update()
{
    //current.swap(next);
    current = next;
    emit hasChanged(this);
}

void Grid::print()
{
    for (CoordType y = 0; y < height; ++y)
    {
        for (CoordType x = 0; x < width; ++x)
        {
            std::cout << int(getValueAt(x, y)) << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Grid::GameOfLifeFiller(Grid& grid, int x, int y)
{
    //Requires every cell to be either 0 or 1 !
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


}

void Grid::RandomBinaryFiller(Grid& grid, int x, int y)
{
    grid.setNextValueAt(x, y, qrand()%2);


}

void Grid::GameOfLifeStep()
{
    fill(GameOfLifeFiller);
}

void Grid::paint(QPaintDevice* device) const
{
    if(!device)
        return;


    QPainter painter(device);
    painter.setBrush(QBrush(QColor(255, 255, 255)));

    painter.setWindow(0, 0, width, height);
    painter.drawRect(0, 0, width, height);



    painter.setBrush(QBrush(QColor(0, 0, 0)));

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (getValueAt(x, y) == 1)
            painter.drawRect(x * 1, y * 1, 1, 1);
        }
    }
}

bool Grid::isActive() const
{
    return active;
}

void Grid::setActive(bool active)
{
    this->active = active;
}

void Grid::switchActive()
{
    setActive(!isActive());
}

void Grid::saveToFile() const
{
    QPixmap pic(width, height);
    paint(&pic);
    pic.save("exported.png");
}
