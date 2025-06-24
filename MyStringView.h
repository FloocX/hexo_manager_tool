#pragma once

#ifndef MYSTRINGVIEW_H
#define MYSTRINGVIEW_H

#include <QScrollArea>
#include <QPushButton>
#include <QGridLayout>
#include <QTimer>


class MyStringView : public QScrollArea{
    Q_OBJECT

public:

    explicit MyStringView(QWidget *parent = nullptr);

    void setStringList(const QStringList &list, QWidget *parent1);
    void addStringList(const QString &tag, QWidget *parent1);
    QStringList getSelectedItems() const;
    QStringList deleteSelectedNewTags();

    QStringList addedTags;

private slots:
    void onButtonClicked();

signals:
    void enableDeleteTagButton(bool enable);
private:
    QWidget *container;
    QVBoxLayout *vLayout;
    QSet<QPushButton*> selectedButtons;
    qint8 tags_count;
    QHBoxLayout* latestRow;
    QSet<QPushButton*> newButtons;

    void updateButtonStyle(QPushButton *button, bool selected);


};

#endif // MYSTRINGVIEW_H
