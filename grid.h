/**
  *     \file grid.h
  *     \author Boris Martin
  *     \brief Class handling a cellular automaton as data.
  *
  */


#ifndef GRID_H
#define GRID_H

#include <vector>
#include <QObject>

class QPaintDevice;


/**      @brief The Grid class
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
 *      CoordType is a typedef for int.
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

        /**
         * @brief Makes changes effective
         *
         * All values modified via setNextValueAt() will become current.
         */
        void update(); //Swap current and next

        /**
         * @brief Prints current data in the console using cout
         *
         * Its main purpose is debugging
         */
        void print();

        /**
         * @brief Paints grid data on a QPaintDevice.
         * @param device : Device where data will be painted on
         *
         * Remember that for some devices, painting must be done on paintEvent()
         */
        void paint(QPaintDevice* device);


        /**
         * @brief Is processing active ?
         * @return true if active, false otherwise.
         */
        bool isActive() const;

        /**
         * @brief Get width of the grid.
         * @return width of the grid
         */
        CoordType getWidth() const {return width;}

        /**
         * @brief Get height of the grid.
         * @return height of the grid
         */
        CoordType getHeight() const {return height;}

        /**
         * @brief Get outOfBoundsValue, a constant fixed at construction time
         * @return outOfBoundsValue
         */
        char getOutOfBoundsValue() const {return outOfBoundsValue;}


        /**
         * @brief Mutate every cell with func, then update()
         * @param func : function to call to mutate a cell.
         *
         * func must be a function with parameters (Grid&, CoordType, CoordType)
         *
         */
        template <class GridFiller> void fill(GridFiller func)  //Takes a function convertible to a std::function<void(Grid&, CoordType, CoordType)>
                                                                //This function must update (via setNextValueAt) any cell knowing it's coord. It will be called with all possibles coords. Then, update is called.
                                                                //It is allowed to read current state, but it's user responsibility to ensure current is valid
        {

            if (!active) //If update is disabled, do nothing
                return;

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
        bool active = true;



    public: //Examples filler

        /**
         * @brief Sample rule to advance Conway's Game of Life simulation.
         * @param grid : reference to the Grid to mutate
         * @param x : absciss of the point to mutate
         * @param y : ordinate of the point to mutate
         *
         * Sample, valid parameter, for fill(). Best way to use it si via GameOfLifeStep().
         * It requires the grid to be either 0 or 1 on every cell
         */
        static void GameOfLifeFiller(Grid& grid, int x, int y);

    public slots:

        /**
         * @brief Calls fill() with Conway's Game of Life's rule
         *
         * This rule is the static public method GameOfLifeFiller()
         */
        void GameOfLifeStep();

        /**
         * @brief TODO : pause or unpause processing
         * @param active : true to make it active, false to pause the process
         */
        void setActive(bool active = true);

        /**
         * @brief same as setActive(!isActive();
         */
        void switchActive();
};

#endif // GRID_H
