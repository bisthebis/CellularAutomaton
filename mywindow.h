#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>
#include <QLabel>
#include "gameoflifepixmap.h"

class Grid;

class MyWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit MyWindow(QWidget *parent = 0, Grid* grid = nullptr);


        QLabel* label;
        GameOfLifePixmap map;

    public slots:
        void updateLabel();
};

#endif // MYWINDOW_H
