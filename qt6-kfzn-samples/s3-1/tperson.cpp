#include "tperson.h"

TPerson::TPerson(QString name, QObject *parent)
    : QObject{parent}
{
    _name = name;
}

TPerson::~TPerson() {
    qDebug("~TPerson()");
}

int  TPerson::age(){
    return _age;
}

void TPerson::setAge(int value) {
    if (_age != value){
        _age = value;
        emit ageChanged(_age); // 发射信号
    }
}

void TPerson::incAge(){
    _age++;
    emit ageChanged(_age); // 发射信号
}
