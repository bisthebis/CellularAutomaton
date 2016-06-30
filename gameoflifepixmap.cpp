#include "gameoflifepixmap.h"
#include "grid.h"

#include <QPainter>
#include <QBrush>
#include <QPixmap>
#include <QFile>


GameOfLifePixmap::GameOfLifePixmap(int w, int h) : width(w), height(h)
{

}

GameOfLifePixmap::~GameOfLifePixmap()
{
    QFile file("export_map.png");
    file.open(QIODevice::WriteOnly);
    pixmap->save(&file, "PNG");
}

void GameOfLifePixmap::setGrid(Grid* src)
{
    linkedGrid = src;
    this->width = src->getWidth();
    this->height = src->getHeight();

    this->pixmap = std::make_unique<QPixmap>(width * cellSize, height * cellSize);

    connect(src, SIGNAL(hasChanged(Grid*)), this, SLOT(updatePixmap(Grid*)));
}


void GameOfLifePixmap::updatePixmap(Grid* src)
{
    QPainter painter(pixmap.get());
    (pixmap->fill());
    //QBrush white = QBrush(QColor(255, 255, 255));
    QBrush black = QBrush(QColor(0, 0, 0));
    painter.setBrush(black);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (src->getValueAt(x, y) == 1)
            painter.drawRect(x * cellSize, y * cellSize, cellSize, cellSize);
        }
    }


}
