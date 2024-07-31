#include "mythread.h"
#include <QSemaphore>

#define BUF_SIZE 10

int buffer1[BUF_SIZE];
int buffer2[BUF_SIZE];
int cur_buf_num = 1;
int buf_seq = 0;
QSemaphore emptybufs(2);    // 空缓冲区的个数，初始资源个数为2
QSemaphore fullbufs;        // 满缓冲区的个数，初始资源个数为0


TDaqThread::TDaqThread(QObject *parent) : QThread{parent}
{}



void TDaqThread::stopThread() {
    stoped_ = true;
}


void TDaqThread::run() {
    stoped_ = false;
    int cnt = 0;
    buf_seq = 0;
    int *buf;

    int n = emptybufs.available();
    if (n < 2)
        emptybufs.release(2 - n);       // 确保开始emptyBufs资源数=2

    while (!stoped_) {
        emptybufs.acquire(1);

        buf = cur_buf_num == 1 ? buffer1 : buffer2;
        for (int i = 0; i < BUF_SIZE; i++) {
            buf[i] = cnt++;
        }
        buf_seq++;

        cur_buf_num = cur_buf_num == 1 ? 2 : 1;
        fullbufs.release();
        msleep(10);
    }
    quit();
}


TProcessThread::TProcessThread(QObject *parent) : QThread{parent}
{}

void TProcessThread::run()  {
    stoped_ = false;
    int read_buf[BUF_SIZE];
    int *buf;

    int n = fullbufs.available();
    if (n > 0)
        fullbufs.acquire(n);        // 确保开始fullBufs资源数=0

    while (!stoped_) {
        if (fullbufs.tryAcquire(1, 5)) {
            buf = cur_buf_num == 1 ? buffer2 : buffer1;
            for (int i = 0; i < BUF_SIZE; i++)
                read_buf[i] = buf[i];

            int len = BUF_SIZE;
            emit dataAvailable(buf_seq, read_buf, len);
            emptybufs.release();
        }
    }
}

void TProcessThread::stopThread() {
    stoped_ = true;
}

