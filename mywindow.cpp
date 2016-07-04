#include "mywindow.h"
#include "ui_mywindow.h"

#include "grid.h"

#include <QtWidgets>
#include <iostream>

static constexpr int grid_defSize = 1000;

MyWindow::MyWindow() :
    QWidget(nullptr),
    ui(new Ui::MyWindow)
{
    ui->setupUi(this);

    Grid* g = new Grid(grid_defSize, grid_defSize);
    g->fill(Grid::RandomBinaryFiller);
    ui->m_GridWidget->setGrid(g);

    connect(ui->pauseButton, &QPushButton::clicked, ui->m_GridWidget, &GridWidget::mustSwitchGridState);

    timer.setInterval(50);
    connect(&timer, &QTimer::timeout, ui->m_GridWidget, &GridWidget::mustAdvanceGameOfLifeStep);
    timer.start();

}

MyWindow::~MyWindow()
{
    delete ui;
}

void MyWindow::on_speedSlider_valueChanged(int value)
{
    timer.setInterval(value);
}

void MyWindow::on_restartButton_clicked()
{
    Grid* g = new Grid(grid_defSize, grid_defSize);
    g->fill(Grid::RandomBinaryFiller);
    ui->m_GridWidget->setGrid(g);
}

void MyWindow::on_saveButton_clicked()
{
    ui->m_GridWidget->getCurrentGrid().saveToFile();
}
