#include "gridwidget.h"
#include "grid.h"


GridWidget::GridWidget(QWidget *parent, Grid* g) : QWidget(parent), grid(nullptr)
{
    if(g)
        setGrid(g);
}
void GridWidget::paintEvent(QPaintEvent *)
{
    grid->paint(this);
}
void GridWidget::setGrid(Grid* g)
{
    if(grid)    //Deletes previous Grid (and the connexion at the same time)
        delete grid;

    this->grid = g;
    grid->setParent(this);
    connect(grid, &Grid::hasChanged, this, &GridWidget::update);
}
void GridWidget::update()
{
    this->QWidget::update();
}
