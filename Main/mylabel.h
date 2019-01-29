#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QTime>
#include <QTimer>
#include <vector>
class word
{
public:
    word(int x ,QString y)
    {
        type = x;
        s = y;
    }
    int type;//0 for number,1 for sentence,2 for images
    QString s;

};

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    MyLabel(int num,int pernum,int);
    int generateRandomInteger(int min, int max);
    QTimer * m_timer;
    QTimer * egg_timer;
    int width = 800;
    int randomMode = 0;
    int numPerRun = 6;
private:
    int timeStep = 30;
    int number;
    int range = 1000;
    bool is_used[10000];
    QList<word>  list;
    int now_value;
    bool is_rolling = false;
    bool is_showing_egg = false;
public slots:
    void startChangeValue();
    void change();
    void showegg();
    void big()
    {
        randomMode = 0;
    }
    void small()
    {
        randomMode = 1;
    }
};

#endif // MYLABEL_H
