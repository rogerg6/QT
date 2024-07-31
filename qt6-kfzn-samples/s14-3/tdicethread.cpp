#include "tdicethread.h"
#include <QRandomGenerator>
#include <QReadWriteLock>
#include <QWaitCondition>


QReadWriteLock rwLocker;
QWaitCondition waiter;
int seq = 0, dice_value = 0;


TDiceThread::TDiceThread(QObject *parent) : QThread{parent}
{}

void TDiceThread::diceBegin() {
    paused_ = false;
}

void TDiceThread::dicePause(){
    paused_ = true;
}

void TDiceThread::stopThread() {
    stoped_ = true;
}


void TDiceThread::run() {
    stoped_ = false;
    paused_ = true;
    seq = 0;
    while (!stoped_) {
        if (!paused_) {
            rwLocker.lockForWrite();

            dice_value = QRandomGenerator::global()->bounded(1, 7);
            seq++;

            waiter.wakeAll();
            rwLocker.unlock();
        }
        msleep(500);
    }
    quit();
}


TDiceValThread::TDiceValThread(QObject *parent) : QThread{parent}
{}

void TDiceValThread::run()  {
    while (1) {
        rwLocker.lockForRead();
        waiter.wait(&rwLocker);
        emit newValue(seq, dice_value);
        rwLocker.unlock();
    }
}

TDicePicThread::TDicePicThread(QObject *parent) : QThread{parent}
{}

void TDicePicThread::run()  {
    while (1) {
        rwLocker.lockForRead();
        waiter.wait(&rwLocker);
        QString filename = QString::asprintf(":/image/images/d%d.jpg", dice_value);
        emit newPicture(filename);
        rwLocker.unlock();
    }
}

