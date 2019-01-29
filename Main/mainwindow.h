#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mylabel.h"
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int num,int pernum,QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *ev) override;
    void resizeEvent(QResizeEvent *event) override;
    QAction *action1,*action2;
private:
    QPoint dragPosition;
    MyLabel *label;
    QMenuBar *mbar;
    QPushButton button;

    QPushButton modeButton;
    void changeButtonPic(bool);
    QLabel* l;
    int width = 800;
    QPixmap backGround = QPixmap(":/backgrounf/background.png");
    QPixmap logo = QPixmap(":/backgrounf/pku1.png");
};

#endif // MAINWINDOW_H
