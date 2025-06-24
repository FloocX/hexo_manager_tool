#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent), selected(4, QVector<bool>(4, false)) {}

int TableModel::rowCount(const QModelIndex &) const { return 4; }
int TableModel::columnCount(const QModelIndex &) const { return 4; }

QVariant TableModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        return QString("Button %1,%2").arg(index.row()).arg(index.column());
    }
    if (role == Qt::UserRole) {
        return selected[index.row()][index.column()];
    }
    return QVariant();
}

bool TableModel::isSelected(int row, int col) const {
    return selected[row][col];
}

void TableModel::toggleSelected(int row, int col) {
    selected[row][col] = !selected[row][col];
    emit dataChanged(index(row, col), index(row, col));
}
