#ifndef TAGSMODEL_H
#define TAGSMODEL_H
#include <QAbstractTableModel>

class TagsModel : public QAbstractTableModel {
    Q_OBJECT
public:
    TagsModel(QObject* parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
private:

};


#endif // TAGSMODEL_H
