#include "tdicethread.h"
#include <QRandomGenerator>


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
    seq_ = 0;
    while (!stoped_) {
        if (!paused_) {
            mtx_.lock();
            dice_val_ = QRandomGenerator::global()->bounded(1, 7);
            seq_++;
            mtx_.unlock();
        }
        msleep(500);
    }
    quit();
}

bool TDiceThread::readNewValue(int &seq, int &dice_val) {
    if (mtx_.tryLock(100)){      // 尝试锁定mutex，等待100ms
        seq = seq_;
        dice_val = dice_val_;
        mtx_.unlock();
        return true;
    } else {
        return false;
    }
}
