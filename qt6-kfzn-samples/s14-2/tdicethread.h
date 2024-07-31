#ifndef TDICETHREAD_H
#define TDICETHREAD_H

#include <QThread>
#include <QMutex>

class TDiceThread : public QThread
{
    Q_OBJECT

private:
    QMutex mtx_;
    int seq_ = 0;               // 投骰子次数的序号
    int dice_val_;              // 骰子点数
    bool paused_ = true;        // 暂停
    bool stoped_ = false;       // 停止线程

protected:
    void run();

public:
    TDiceThread(QObject *parent = nullptr);
    void diceBegin();
    void dicePause();
    void stopThread();

    bool readNewValue(int &seq, int &dice_val);
};

#endif // TDICETHREAD_H
