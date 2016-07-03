#include "mywindow.h"
#include "ui_mywindow.h"

#include "grid.h"

MyWindow::MyWindow(Grid* g) :
    QWidget(nullptr),
    ui(new Ui::MyWindow)
{
    ui->setupUi(this);
    ui->m_Grid->setGrid(g);
}

MyWindow::~MyWindow()
{
    delete ui;
}
