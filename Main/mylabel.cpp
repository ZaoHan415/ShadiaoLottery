#include "mylabel.h"
#include <QObject>
#include <QDebug>
MyLabel::MyLabel(int num,int pernum,int wid)
{
    range = num;
    numPerRun = pernum;
    width = wid;
    memset(is_used,0,sizeof(is_used));
    setAlignment(Qt::AlignCenter);
    setStyleSheet("color:#d60000;"
                  "font-family:"";"
                  "background:transparent");

    m_timer = new QTimer();
    for(int i = 0;i<=range;i++){
        list.append(word(0,QString::number(i)));
    }
    now_value = generateRandomInteger(1,range);
    setFont(QFont("Times", 0.05*width, QFont::Bold));
    egg_timer = new QTimer();
}

void MyLabel::startChangeValue()
{
    if(randomMode == 0){
        setStyleSheet("color:#d60000;"
                      "font-family:"";"
                      "background:transparent");
        resize(0.17*width,0.08*width);
        move(0.418*width,0.28*width);
        if(!is_rolling){
            m_timer->start(timeStep);
            is_rolling = true;
        }
        else{
            m_timer->stop();
            range --;
            list.removeAt(now_value);
            is_rolling = false;
        }
    }
    else{
        QString s;
        for(int i = 0;i<numPerRun;i++){
            int order = generateRandomInteger(1,range);
            s = s + list.at(order).s +'\n';
            list.removeAt(order);
            range --;
        }
        setStyleSheet("color:#0000;"
                      "font-family:"";");
        setStyleSheet("background:transparent");
        setAlignment(Qt::AlignHCenter);
        setFont(QFont("Times", 0.03*width, QFont::Bold));
        qDebug() << s;
        resize(0.17*width,0.26*width*numPerRun/6);
        move(0.418*width,0.23*width);
        setText(s);
    }
}

int MyLabel::generateRandomInteger(int min,int max)
{
    Q_ASSERT(min < max);
    static bool seedStatus;
    if (!seedStatus)
    {
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        seedStatus = true;
    }
    int nRandom = qrand() % (max + 1 - min);

    nRandom = min + nRandom;
    return nRandom;
}

void MyLabel::change()
{
    setFont(QFont("Times", 0.06*width, QFont::Bold));
    if(randomMode == 0){
        //this->show();
        now_value = generateRandomInteger(1,range);
        if(list.at(now_value).type == 0)
            this->setText(list.at(now_value).s);
        else if(list.at(now_value).type == 1){
            setFont(QFont("Times", 30));
            setStyleSheet("color:black;"
                          "font-family:Kai;");
            this->setGeometry(0,0,width,0.8*width);
            this->setText(list.at(now_value).s);
            egg_timer->start(1000);
            m_timer->stop();
        }
        else if(list.at(now_value).type == 2){
            QPixmap cir(list.at(now_value).s);
            setPixmap(cir);
            resize(cir.size());
            move(0.375*width,0.2*width);
            show();
            egg_timer->start(1000);
            m_timer->stop();
        }
    }
}

void MyLabel::showegg()
{
    list.removeAt(now_value);
    range --;
    egg_timer->stop();
    m_timer->start(timeStep);
    setStyleSheet("color:#d60000;"
                  "font-family:"";"
                  "background:transparent");
    setFont(QFont("Times", 60, QFont::Bold));
    setGeometry(0.418*width,0.280*width,0.150*width,0.080*width);
}
