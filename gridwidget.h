/**
  *     \file gridwidget.h
  *     \author Boris Martin
  *     \brief Widget linked to a Grid meant to be used as a Grid::paint() target.
  *
  */


#ifndef GAMESHOWER_H
#define GAMESHOWER_H

#include <QWidget>
#include <memory>
#include "grid.h"



/**
 * @brief Widget linked to a Grid meant to be used as a Grid::paint() target.
 *
 * Widget linked to a Grid (owned or not) meant to be a target PaintDevice. Assuming its update slot is linked to hasChanged signal of Grid, it will show its state
 * by calling Grid::paint on itself (in paintEvent).
 *
 * GridWidget takes ownership of its Grid.
 */

class GridWidget : public QWidget
{
    private:
        Q_OBJECT

        /**
         * @brief paints owned Grid on itself
         * @param event : unused
         *
         * Calls Grid::paint() on itself.
         */
        virtual void paintEvent(QPaintEvent *event);

        std::unique_ptr<Grid> grid;
    public:

        /**
         * @brief Constructor
         * @param parent : parent Widget
         * @param grid : Grid to link on and take ownership of.
         */
        explicit GridWidget(QWidget *parent = 0, Grid* grid = nullptr);

        /**
         * @brief Changes current linked Grid.
         * @param grid : Grid to link on and take ownership of.
         */
        void setGrid(Grid* grid);

    signals:
        /**
         * @brief Forwards owned grid call to GameOfLifeStep()
         */
        void mustAdvanceGameOfLifeStep();

        /**
         * @brief Forwards owned gril call to SwitchActive()
         */
        void mustSwitchGridState();

    public slots:
        /**
         * @brief Regular QWidget::update() slot, without change.
         */
        void update();


};

#endif // GAMESHOWER_H
