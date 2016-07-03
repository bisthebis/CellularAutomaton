#include "gridwidget.h"


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


    this->grid = std::unique_ptr<Grid>(g);
    //grid->setParent(this); No more since unique_ptr
    connect(grid.get(), &Grid::hasChanged, this, &GridWidget::update);
    connect(this, &GridWidget::mustAdvanceGameOfLifeStep, grid.get(), &Grid::GameOfLifeStep);
    connect(this, &GridWidget::mustSwitchGridState, grid.get(), &Grid::switchActive);
}
void GridWidget::update()
{
    this->QWidget::update();
}
