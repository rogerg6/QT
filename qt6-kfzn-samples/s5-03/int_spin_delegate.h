#ifndef INT_SPIN_DELEGATE_H
#define INT_SPIN_DELEGATE_H

#include <QStyledItemDelegate>


class IntSpinDelegate : public QStyledItemDelegate {
    Q_OBJECT
private:
    QStringList item_list_;
    bool editable_;
public:
    explicit IntSpinDelegate(QObject *parent = nullptr);

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



#endif // INT_SPIN_DELEGATE_H
