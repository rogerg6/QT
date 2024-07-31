#ifndef TDICETHREAD_H
#define TDICETHREAD_H

#include <QThread>

class TDiceThread : public QThread
{
    Q_OBJECT

private:

    bool paused_ = true;        // 暂停
    bool stoped_ = false;       // 停止线程

protected:
    void run();

public:
    TDiceThread(QObject *parent = nullptr);
    void diceBegin();
    void dicePause();
    void stopThread();
};


// 消费dice value的线程, 发送newValue信号
class TDiceValThread : public QThread
{
    Q_OBJECT

protected:
    void run();

public:
    TDiceValThread(QObject *parent = nullptr);

signals:
    void newValue(int seq, int dice_val);       // 产生新点数的信号
};


// 消费dice value的线程, 发送newPicture信号
class TDicePicThread : public QThread
{
    Q_OBJECT

protected:
    void run();

public:
    TDicePicThread(QObject *parent = nullptr);

signals:
    void newPicture(QString filename);
};

#endif // TDICETHREAD_H
