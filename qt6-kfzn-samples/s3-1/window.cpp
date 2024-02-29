#include "window.h"
#include "ui_window.h"
#include <QMetaProperty>

Window::Window(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    boy = new TPerson("王小明", this);
    boy->setProperty("score", 93);
    boy->setProperty("age", 20);
    ui->spinBoy->setValue(boy->age());
    boy->setProperty("sex", "Boy");
    connect(boy, SIGNAL(ageChanged(int)), this, SLOT(do_ageChanged(int)));

    girl = new TPerson("张小丽", this);
    girl->setProperty("score", 83);
    girl->setProperty("age", 28);
    ui->spinGirl->setValue(girl->age());
    girl->setProperty("sex", "Girl");
    connect(girl, SIGNAL(ageChanged(int)), this, SLOT(do_ageChanged(int)));

    ui->spinBoy->setProperty("isBoy", true);
    ui->spinGirl->setProperty("isBoy", false);

    connect(ui->spinGirl, SIGNAL(valueChanged(int)), this, SLOT(do_spinChanged(int)));
    connect(ui->spinBoy, &QSpinBox::valueChanged, this, &Window::do_spinChanged);
}

Window::~Window() {
    delete ui;
}

void Window::do_ageChanged(int value) {
    Q_UNUSED(value);
    TPerson *person = qobject_cast<TPerson*>(sender());
    QString name = person->property("name").toString();
    QString sex = person->property("sex").toString();
    int age = person->age();
    // int age = peron->property("age").toInt();       // 通过属性获取年龄数据

    QString info = QString("%1, %2, 年龄=%3").arg(name).arg(sex).arg(age);
    ui->textEdit->appendPlainText(info);
}

void Window::do_spinChanged(int value) {
    QSpinBox *spinBox = qobject_cast<QSpinBox*>(sender());
    if (spinBox->property("isBoy").toBool())
        boy->setAge(value);
    else
        girl->setAge(value);
}


void Window::on_btnBoyInc_clicked() {
    boy->incAge();
}

void Window::on_btnGirlInc_clicked()
{
    girl->incAge();
}


void Window::on_btnClear_clicked()
{
    ui->textEdit->clear();
}


void Window::on_btnClassInfo_clicked()
{
    QObject *obj = boy;
    const QMetaObject  *meta = obj->metaObject();

    ui->textEdit->clear();
    ui->textEdit->appendPlainText(QString("类名： %1\n").arg(meta->className()));
    ui->textEdit->appendPlainText("Property");

    for (int i = meta->propertyOffset(); i < meta->propertyCount(); i++) {
        const char *propName = meta->property(i).name();
        QString propValue = obj->property(propName).toString();
        QString str = QString("属性名称=%1， 属性值=%2").arg(propName).arg(propValue);
        ui->textEdit->appendPlainText(str);
    }

    ui->textEdit->appendPlainText("");
    ui->textEdit->appendPlainText("classInfo");

    for (int i = meta->classInfoOffset(); i < meta->classInfoCount();i++) {
        QMetaClassInfo classInfo = meta->classInfo(i);
        ui->textEdit->appendPlainText(QString("Name=%1, Value=%2").arg(classInfo.name()).arg(classInfo.value()));
    }
}

