#include "gridwidget.h"
#include "grid.h"
GridWidget::GridWidget(QWidget *parent, Grid* g) : QWidget(parent), grid(g)
{

}
void GridWidget::paintEvent(QPaintEvent *)
{
    grid->paint(this);
}
void GridWidget::setGrid(Grid* g)
{
    this->grid = g;
    grid->setParent(this);
}
void GridWidget::update()
{
    this->QWidget::update();
}
