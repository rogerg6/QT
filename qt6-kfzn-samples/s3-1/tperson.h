#ifndef TPERSON_H
#define TPERSON_H

#include <QObject>

class TPerson : public QObject
{
    Q_OBJECT

    // 定义类的附加信息
    Q_CLASSINFO("author", "rogerg6")
    Q_CLASSINFO("company", "zhxk")
    Q_CLASSINFO("version", "2.0.0")

    // 定义属性
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(QString name MEMBER _name)
    Q_PROPERTY(int score MEMBER _score)

private:
    int _age = 10;
    int _score = 79;
    QString _name;

public:
    explicit TPerson(QString name, QObject *parent = nullptr);
    ~TPerson();

    int age();
    void setAge(int value);
    void incAge();

signals:
    // 自定义信号
    void ageChanged(int value);
};

#endif // TPERSON_H
