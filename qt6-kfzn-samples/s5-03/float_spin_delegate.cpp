
#include "float_spin_delegate.h"
#include <QDoubleSpinBox>

FloatSpinDelegate::FloatSpinDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

QWidget *FloatSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,\
                                         const QModelIndex &index) const {
    Q_UNUSED(option);
    Q_UNUSED(index);
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setFrame(false);        // 组件的属性设置
    editor->setMinimum(0);
    editor->setMaximum(20000);
    editor->setDecimals(2);         // 小数点位数
    return editor;
}


void FloatSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    float value = index.model()->data(index, Qt::EditRole).toFloat();
    QDoubleSpinBox *spinbox = static_cast<QDoubleSpinBox*>(editor);
    spinbox->setValue(value);
}

void FloatSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    QDoubleSpinBox *spinbox = static_cast<QDoubleSpinBox*>(editor);
    float value = spinbox->value();
    QString str = QString::asprintf("%.2f", value);
    model->setData(index, str, Qt::EditRole);
}

void FloatSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, \
                                             const QModelIndex &index) const{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
