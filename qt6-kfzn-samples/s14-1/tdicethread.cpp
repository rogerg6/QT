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
            dice_val_ = QRandomGenerator::global()->bounded(1, 7);
            seq_++;
            emit newValue(seq_, dice_val_);
        }
        msleep(500);
    }
    quit();
}
