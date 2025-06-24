#ifndef BUTTONDELEGATE_H
#define BUTTONDELEGATE_H

#include <QStyledItemDelegate>
#include <QPushButton>

class ButtonDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ButtonDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index) override;
};

#endif // BUTTONDELEGATE_H
