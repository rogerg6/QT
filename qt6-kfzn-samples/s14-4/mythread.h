#ifndef TDICETHREAD_H
#define TDICETHREAD_H

#include <QThread>

class TDaqThread : public QThread
{
    Q_OBJECT

private:
    bool stoped_ = false;       // 停止线程

protected:
    void run();

public:
    TDaqThread(QObject *parent = nullptr);
    void stopThread();

};


// 消费dice value的线程, 发送newValue信号
class TProcessThread : public QThread
{
    Q_OBJECT

private:
    bool stoped_ = false;

protected:
    void run();

public:
    TProcessThread(QObject *parent = nullptr);
    void stopThread();

signals:
    void dataAvailable(int buf_seq, int *buf, int len);       // 产生新点数的信号
};



#endif // TDICETHREAD_H
