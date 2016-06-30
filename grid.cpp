#include "grid.h"

#include <iostream>

Grid::Grid(CoordType width, CoordType height, char outOfBoundsValue) :
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
