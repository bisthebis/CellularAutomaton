#ifndef GAMEOFLIFEPIXMAP_H
#define GAMEOFLIFEPIXMAP_H


#include <QObject>
#include <QPixmap>
#include <memory>

class Grid;

class GameOfLifePixmap : public QObject
{
    private:
        Q_OBJECT

        int width;
        int height;
        Grid* linkedGrid;
        std::unique_ptr<QPixmap> pixmap;

    public:
        GameOfLifePixmap(int w = 0, int h = 0);
        ~GameOfLifePixmap();
        void setGrid(Grid* src);
        const QPixmap& getPixmap() const {return *pixmap;}

        const int cellSize = 1; // 5 px per cell

    public slots:
        void updatePixmap(Grid* src);

};

#endif // GAMEOFLIFEPIXMAP_H
