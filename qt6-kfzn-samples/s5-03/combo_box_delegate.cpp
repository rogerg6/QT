#include "combo_box_delegate.h"

ComboBoxDelegate::ComboBoxDelegate(QObject *parent): QStyledItemDelegate(parent){}

void ComboBoxDelegate::setItems(QStringList items, bool editable){
    item_list_ = items;
    editable_ = editable;
}


// 创建代理编辑器
QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,\
                                        const QModelIndex &index) const {
    Q_UNUSED(option);
    Q_UNUSED(index);
    QComboBox *editor = new QComboBox(parent);
    editor->setEditable(editable_);
    for (int i = 0; i < item_list_.count(); ++i)
        editor->addItem(item_list_.at(i));
    return editor;
}

// 双击单元格时，加载model中的数据到editor
void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *combobox = static_cast<QComboBox*>(editor);
    combobox->setCurrentText(value);
}

// 设置editor中的数据到model中
void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    QComboBox *combobox = static_cast<QComboBox*>(editor);
    QString value = combobox->currentText();
    model->setData(index, value, Qt::EditRole);
}

// 更新组件大小
void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, \
                                            const QModelIndex &index) const {
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
