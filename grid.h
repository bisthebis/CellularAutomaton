/**
  *     \file grid.h
  *     \author Boris Martin
  *     \brief Class handling a cellular automaton as data.
  *
  *
  *
  *
  *
  */


#ifndef GRID_H
#define GRID_H

#include <vector>
#include <QObject>

class QPaintDevice;


/**     @class Grid grid.h grid.cpp
 *      @brief The Grid class
 *
 *
 *      Data class for managing state of a rectangular cellular automaton.
 *      Use fill(func) method to go to the next generation, using "func" as a function taking a reference to the Grid, x and y coordinates, and changes the grid on that place.
 *      Every time fill is called, a "hasChanged" signal is emitted, with "this" pointer as parameter
 *      At the moment, grid size must be know at construction time
 *
 *      The class provides method "GameOfLifeStep()", which calls "fill" with Conway's Game of Life's rule as argument.
 *      It also provides "print" method, showing the grid using std::cout. It's main purpose is debugging
 *
 *      Can now paint itself on any QPaintDevice;
 *
 */


class Grid : public QObject
{

    using CoordType = int;

    private:
        Q_OBJECT

    signals:
        /**
         * @brief Signal when "current" data changes
         * @param self : pointer to the grid, a.k.a "this"
         */
        void hasChanged(Grid* self);

    public:
        /**
         * @brief Constructor
         * @param width : number of columns in the grid. Can't be changed later
         * @param height : number of rows in the grid. Can't be changed later
         * @param outOfBoundsValue : Value returned whenuser tries to get value bordering the grid.
         * @param parent : parent in QObject hierarchy
         */
        Grid(CoordType width = 0, CoordType height = 0, char outOfBoundsValue = 0, QObject* parent = nullptr);

        /**
         * @brief Gets current value at (x, y)
         * @param x : absciss of the queried value
         * @param y : ordinate of the queried value
         * @return either current[x+y*width] or outOfBoundsValue, deepending on whether x and y are in range [0, width[ and [0, height[
         */
        char getValueAt(CoordType x, CoordType y) const;

        /**
         * @brief set next value "value" at (x, y). It will be effective when update() gets called.
         * @param x : absciss of the changed value
         * @param y : ordinate of the changed value
         * @param value : new value1
         *
         * Does nothing is out of range [0, width[ or [0, height[
         */
        void setNextValueAt(CoordType x, CoordType y, char value);
        void update(); //Swap current and next

        void print(); //To "cout"
        void paint(QPaintDevice* device);

        CoordType getWidth() const {return width;}
        CoordType getHeight() const {return height;}
        char getOutOfBoundsValue() const {return outOfBoundsValue;}



        template <class GridFiller> void fill(GridFiller func)  //Takes a function convertible to a std::function<void(Grid&, CoordType, CoordType)>
                                                                //This function must update (via setNextValueAt) any cell knowing it's coord. It will be called with all possibles coords. Then, update is called.
                                                                //It is allowed to read current state, but it's user responsibility to ensure current is valid
        {

            for (CoordType y = 0; y < height; ++y)
            {
                for (CoordType x = 0; x < width; ++x)
                {
                    func(*this, x, y);
                }
            }

            update();
            return;
        }

    private:
        const char outOfBoundsValue = 0;
        const CoordType width = 0;
        const CoordType height = 0;
        std::vector<char> current;
        std::vector<char> next;



    public: //Examples filler
        static void GameOfLifeFiller(Grid& grid, int x, int y);

    public slots:

        /**
         * @brief Calls fill(func) with Conway's Game of Life's rule
         *
         * This rule is the static public method GameOfLifeFiller
         */
        void GameOfLifeStep();
};

#endif // GRID_H
