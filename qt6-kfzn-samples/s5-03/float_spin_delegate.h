#ifndef FLOAT_SPIN_DELEGATE_H
#define FLOAT_SPIN_DELEGATE_H


#include <QStyledItemDelegate>

class FloatSpinDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit FloatSpinDelegate(QObject *parent = nullptr);

    // 创建代理编辑器
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,\
                                            const QModelIndex &index) const ;

    // 双击单元格时，加载model中的数据到editor
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    // 设置editor中的数据到model中
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    // 更新组件大小
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, \
                              const QModelIndex &index) const;
};

#endif // FLOAT_SPIN_DELEGATE_H
