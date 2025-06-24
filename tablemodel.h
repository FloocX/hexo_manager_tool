#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>

class TableModel : public QAbstractTableModel{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex())const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool isSelected(int row, int col) const;
    void toggleSelected(int row, int col);

private:
    QVector<QVector<bool>> selected;

};

#endif // TABLEMODEL_H
