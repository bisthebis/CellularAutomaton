#include "mywindow.h"
#include <iostream>


MyWindow::MyWindow(QWidget *parent, Grid *grid) : QWidget(parent), label(new QLabel(this))
{
    setFixedSize(500, 500);
    map.setGrid(grid);
    label->setFixedSize(500, 500);
}

void MyWindow::updateLabel()
{
     label->setPixmap(map.getPixmap());
}
