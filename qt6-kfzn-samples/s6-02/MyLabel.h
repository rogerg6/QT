#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

class MyLabel : public QLabel {
    Q_OBJECT

public:
    MyLabel(QWidget *parent = nullptr);
    bool event(QEvent *e);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
signals:
    void doubleClicked();
};

#endif // MYLABEL_H
