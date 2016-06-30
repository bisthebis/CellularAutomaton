#ifndef GRID_H
#define GRID_H

#include <vector>
#include <QObject>

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

        CoordType getWidth() const {return width;}
        CoordType getHeight() const {return height;}

        const char outOfBoundsValue = 0;
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
        CoordType width = 0;
        CoordType height = 0;
        std::vector<char> current;
        std::vector<char> next;



    public: //Examples filler
        static void GameOfLifeFiller(Grid& grid, int x, int y);

    public slots:
        void GameOfLifeStep();
};

#endif // GRID_H
