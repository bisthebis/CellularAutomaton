/**
  *     Widget linked to a Grid (owned or not) meant to be a target PaintDevice. Assuming its update slot is linked to hasChanged signal of Grid, it will show its state
  *     by calling Grid::paint on itself (in paintEvent).
  *
  *     It doesn't require ownership of Grid, but making the grid its child (as a QObject) may be the easiest way to manage this
  *
  *     @author Boris Martin
  *     @version 0.2
  *
  */


#ifndef GAMESHOWER_H
#define GAMESHOWER_H

#include <QWidget>

class Grid;

class GridWidget : public QWidget
{
    private:
        Q_OBJECT
        virtual void paintEvent(QPaintEvent *event);
    public:
        explicit GridWidget(QWidget *parent = 0, Grid* grid = nullptr);
        void setGrid(Grid* grid); //Does NOT link but DOES take ownership
        Grid* grid;
    signals:

    public slots:
        void update();
};

#endif // GAMESHOWER_H
