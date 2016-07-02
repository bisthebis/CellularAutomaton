/**
  *     Data class for managing state of a rectangular cellular automaton.
  *     Use fill(func) method to go to the next generation, using "func" as a function taking a reference to the Grid, x and y coordinates, and changes the grid on that place.
  *     Every time fill is called, a "hasChanged" signal is emitted, with "this" pointer as parameter
  *     At the moment, grid size must be know at construction time
  *
  *     The class provides method "GameOfLifeStep()", which calls "fill" with Conway's Game of Life's rule as argument.
  *     It also provides "print" method, showing the grid using std::cout. It's main purpose is debugging
  *
  *     Can now paint itself on any QPaintDevice;
  *
  *     @author Boris Martin
  *     @version 0.3
  *
  */


#ifndef GRID_H
#define GRID_H

#include <vector>
#include <QObject>

class QPaintDevice;

class Grid : public QObject
{

    using CoordType = int;

    private:
        Q_OBJECT

    signals:
        hasChanged(Grid* self);

    public:
        Grid(CoordType width = 0, CoordType height = 0, char outOfBoundsValue = 0, QObject* parent = nullptr);
        char getValueAt(CoordType x, CoordType y) const;
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
        void GameOfLifeStep();
};

#endif // GRID_H
