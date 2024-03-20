
#include "int_spin_delegate.h"
#include <QSpinBox>

IntSpinDelegate::IntSpinDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

QWidget *IntSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,\
                                         const QModelIndex &index) const {
    Q_UNUSED(option);
    Q_UNUSED(index);
    QSpinBox *editor = new QSpinBox(parent);
    editor->setFrame(false);        // 组件的属性设置
    editor->setMinimum(0);
    editor->setMaximum(20000);

    return editor;
}


void IntSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    int value = index.model()->data(index, Qt::EditRole).toFloat();
    QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
    spinbox->setValue(value);
}

void IntSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
    int value = spinbox->value();
    QString str = QString::asprintf("%d", value);
    model->setData(index, str, Qt::EditRole);
}

void IntSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, \
                                             const QModelIndex &index) const{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
