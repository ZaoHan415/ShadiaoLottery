#include "mainwindow.h"
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <sstream>
#include <string>
#include <iostream>

MainWindow::MainWindow(int num,int pernum,QWidget *parent)
    : QMainWindow(parent)
{

    mbar = new QMenuBar();
    QMenu *menu = new QMenu("大哥抽什么");
    action1 = new QAction("抽大的", NULL);
    action2 = new QAction("抽小的",NULL);
    menu->addAction(action1);
    menu->addAction(action2);
    mbar->addMenu(menu);
    setMenuBar(mbar);


    setMouseTracking(true);
    setWindowTitle("一本正经的摇号机");
    backGround = backGround.scaledToWidth(width);
    //QBitmap bitBack = backGround.mask();
    resize(backGround.size());
    //setMask(bitBack);
    setStyleSheet("background-color:white;");

    /*l = new QLabel(this);
    QPixmap cir(":/emoji/circle.png");
    cir = cir.scaledToWidth(width/4);
    l->setPixmap(cir);
    l->resize(cir.size());
    l->move(width * 0.375 ,width * 0.2);
    l->show();*/

    button.setParent(this);
    button.setStyleSheet("QPushButton{border:0px;}");
    logo = logo.scaledToWidth(0.2*width);
    button.setIcon(logo);
    button.installEventFilter(this);
    button.setIconSize(logo.size());
    button.resize(logo.size());
    button.move(0.4*width,0);
    button.show();
    button.setObjectName("按钮");
    button.setFocus();
    //qDebug() << button.pos();
    //qDebug() <<logo.width() << logo.height();


    label = new MyLabel(num,pernum,width);
    label->resize(0.15*width,0.08*width);
    label->setParent(this);
    label->move(0.419*width,0.28*width);
    label->show();
    label->setFocusPolicy(Qt::NoFocus);


    connect(action1, SIGNAL(triggered()), label, SLOT(big()));
    connect(action2, SIGNAL(triggered()), label, SLOT(small()));

    connect(&button,SIGNAL(pressed()),label,SLOT(startChangeValue()));
    connect(label->m_timer,SIGNAL(timeout()),label,SLOT(change()));
    connect(label->egg_timer,SIGNAL(timeout()),label,SLOT(showegg()));

}

MainWindow::~MainWindow()
{
    delete  label;
    delete action1;
    delete action2;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0,0,backGround.scaledToWidth(width));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p = QPoint( event->pos() );
    QRect r = button.geometry();
    //qDebug() << p << r;
    if(r.contains(p)){
        qDebug() <<"ha";
    }

}

bool MainWindow::eventFilter(QObject *obj, QEvent *ev)
{
    if( obj == &button){
        if( ev->type() == QEvent::Enter ){
            setCursor(Qt::PointingHandCursor);
            changeButtonPic(true);
            return true;
        }
        else if( ev->type() == QEvent::Leave ){
            setCursor(Qt::ArrowCursor);
            changeButtonPic(false);
            return true;
        }
        else
            return QObject::eventFilter(obj, ev);
    }
    return QObject::eventFilter(obj, ev);
}

void MainWindow::changeButtonPic(bool t)
{
    if(t){
        int x = label->generateRandomInteger(1,21);
        std::string num = std::to_string(x);
        if(num.length() == 2){
            num = "0" + num;
        }
        else{
            num = "00"+num;
        }
        std::string name = ":/emoji/PKU_Emoji/IMG_" + num;
        QString n = QString::fromStdString(name);
        qDebug() << n;
        QPixmap logo(n);
        logo = logo.scaledToWidth(0.2*width);
        button.setIcon(logo);
    }
    else{
        QPixmap logo(":/backgrounf/pku1.png");
        logo = logo.scaledToWidth(0.2*width);
        button.setIcon(logo);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    qDebug() << event->size();
    backGround = QPixmap(":/backgrounf/background.png");
    backGround = backGround.scaledToWidth(event->size().width());
    resize(backGround.size());
    width = backGround.width();

    label->width = width;
    label->resize(0.15*width,0.08*width);
    label->move(0.419*width,0.28*width);

    /*QPixmap cir(":/emoji/circle.png");
    cir = cir.scaledToWidth(width/4);
    l->setPixmap(cir);
    l->resize(cir.size());
    l->move(width * 0.375 ,width * 0.2);
    l->resize(width/4,width/4);*/

    logo = QPixmap(":/backgrounf/pku1.png");
    logo = logo.scaledToWidth(0.2*width);
    button.setIcon(logo);
    button.move(0.4*width,0);
    button.resize(logo.size());
}
