#include "mywindow.h"
#include "ui_mywindow.h"

#include "grid.h"

#include <QtWidgets>
#include <iostream>

MyWindow::MyWindow() :
    QWidget(nullptr),
    ui(new Ui::MyWindow)
{
    ui->setupUi(this);

    Grid* g = new Grid(250, 250);
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
    Grid* g = new Grid(250, 250);
    g->fill(Grid::RandomBinaryFiller);
    ui->m_GridWidget->setGrid(g);
}

void MyWindow::on_saveButton_clicked()
{
    ui->m_GridWidget->getCurrentGrid().saveToFile();
}
