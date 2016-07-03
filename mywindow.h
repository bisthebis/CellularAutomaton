#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>
#include <QTimer>


class Grid;

namespace Ui {
class MyWindow;
}

class MyWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit MyWindow();
        ~MyWindow();

private slots:
    void on_speedSlider_valueChanged(int value);

    void on_restartButton_clicked();

private:
        Ui::MyWindow *ui;
        QTimer timer;
};

#endif // MYWINDOW_H
