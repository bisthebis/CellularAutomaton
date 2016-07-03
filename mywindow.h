#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>

class Grid;

namespace Ui {
class MyWindow;
}

class MyWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit MyWindow(Grid*);
        ~MyWindow();

    private:
        Ui::MyWindow *ui;
};

#endif // MYWINDOW_H
