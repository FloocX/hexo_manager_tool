#include "MyStringView.h"

MyStringView::MyStringView(QWidget *parent)
    : QScrollArea(parent)
{
    // 设置内部容器
    container = new QWidget(this);
    vLayout = new QVBoxLayout(container);
    container->setLayout(vLayout);

    // 滚动设置
    setWidget(container);
    setWidgetResizable(true);

    MyStringView::tags_count = 0;

    // 只允许纵向滚动条，禁止横向滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

// void MyStringView::addStringList(const QString &tag){
//     QHBoxLayout* currentRow;
//     if(MyStringView::tags_count == 0){
//         currentRow = new QHBoxLayout();
//         vLayout->addLayout(currentRow);
//         MyStringView::latestRow = currentRow;
//     }else{

//     }

//     int spacing = 8;

//     QFont font("Arial", 12);
//     QFontMetrics metrics(font);

//     int width = metrics.horizontalAdvance(tag);
//     int height = metrics.height();

//     QPushButton *btn = new QPushButton(tag);
//     btn->setCheckable(true);
//     btn->setStyleSheet("background-color: lightgray; color: black;");
//     btn->setFixedSize(width + spacing, height + spacing);
//     btn->setToolTip(tag);
//     // qDebug()<<btn->toolTip();
//     connect(btn, &QPushButton::clicked, this, &MyStringView::onButtonClicked);

//     MyStringView::latestRow->addWidget(btn);

// }

void MyStringView::addStringList(const QString &tag, QWidget *parent1) {

    MyStringView::latestRow = nullptr;

    int spacing = 8;
    QFont font("Arial", 12);
    QFontMetrics metrics(font);

    QString tagText = tag + " (新)";  // 标识为新添加的 tag
    int width = metrics.horizontalAdvance(tagText);
    int height = metrics.height();

    QPushButton *btn = new QPushButton(tagText);
    btn->setCheckable(true);
    btn->setStyleSheet("background-color: lightgray; color: black;");
    btn->setFixedSize(width + spacing, height + spacing);
    btn->setToolTip(tagText);
    connect(btn, &QPushButton::clicked, this, &MyStringView::onButtonClicked);

    // 计算是否能添加到当前行
    if (!MyStringView::latestRow) {
        MyStringView::latestRow = new QHBoxLayout();
        vLayout->addLayout(MyStringView::latestRow);
    }
    QHBoxLayout* row = MyStringView::latestRow;

    qDebug()<<row;
    qDebug()<<row->count();


    // 计算当前行已使用宽度
    int usedWidth = 0;
    for (int i = 0; i < latestRow->count(); ++i) {
        QWidget *w = latestRow->itemAt(i)->widget();
        if (w) {
            usedWidth += w->width() + latestRow->spacing();
        }
    }

    int maxWidth = parent1->width();

    if (usedWidth + btn->width() > maxWidth) {
        // 新建一行
        MyStringView::latestRow = new QHBoxLayout();
        vLayout->addLayout(MyStringView::latestRow);
    }

    MyStringView::latestRow->addWidget(btn);
    newButtons.insert(btn);  // 标记为新加按钮

    addedTags.append(tag);
}


void MyStringView::setStringList(const QStringList &list, QWidget *parent1) {
    // 清空旧内容
    QLayoutItem *item;
    while ((item = vLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    selectedButtons.clear();

    int spacing = 8;
    // QWidget* parent1 = vLayout->parentWidget()->parentWidget()->parentWidget();
    int maxWidth = parent1->width(); // 获取容器最大宽度
    qDebug()<<"容器最大宽度:"<<maxWidth;
    qDebug()<<parent1->objectName();
    qDebug()<<parent1->size();
    QHBoxLayout *currentRow = new QHBoxLayout(); // 当前行布局
    vLayout->addLayout(currentRow);

    for (const QString &text : list) {
        QFont font("Arial", 12);
        QFontMetrics metrics(font);

        int width = metrics.horizontalAdvance(text);
        int height = metrics.height();

        QPushButton *btn = new QPushButton(text);
        btn->setCheckable(true);
        btn->setStyleSheet("background-color: lightgray; color: black;");
        btn->setFixedSize(width + spacing, height + spacing);
        btn->setToolTip(text);
        // qDebug()<<btn->toolTip();
        connect(btn, &QPushButton::clicked, this, &MyStringView::onButtonClicked);
        // qDebug()<<"当前按钮的大小"<<btn->size();
        // 计算当前行已使用的宽度
        int usedWidth = 0;
        for (int i = 0; i < currentRow->count(); ++i) {
            QWidget *widget = currentRow->itemAt(i)->widget();
            if (widget) {
                usedWidth += widget->width() + currentRow->spacing();
            }
        }

        // 检查是否需要新行
        if (usedWidth + width > maxWidth) {
            currentRow = new QHBoxLayout();
            vLayout->addLayout(currentRow);
        }

        currentRow->addWidget(btn);
        // currentRow->setSpacing(spacing);
    }
    vLayout->addStretch();
}

void MyStringView::onButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    bool isSelected = selectedButtons.contains(button);

    if (isSelected) {
        selectedButtons.remove(button);
    } else {
        selectedButtons.insert(button);
    }

    updateButtonStyle(button, !isSelected);

    // 判断是否全部为新增按钮
    bool allNew = !selectedButtons.empty();
    for (QPushButton *btn : selectedButtons) {
        if (!newButtons.contains(btn)) {
            allNew = false;
            break;
        }
    }

    emit enableDeleteTagButton(allNew);  // 发射信号
}

QStringList MyStringView::deleteSelectedNewTags() {
    QStringList deletedTexts;

    for (QPushButton* btn : selectedButtons) {
        if (newButtons.contains(btn)) {
            // 获取原始文本（去掉 " (新)"）
            QString text = btn->text();
            if (text.endsWith(" (新)")) {
                text.chop(4);  // 移除末尾 "(新)" 四个字符
            }
            deletedTexts << text;

            newButtons.remove(btn);
            delete btn;  // 删除按钮
        }
    }

    // 清除已删除的按钮引用
    selectedButtons.clear();

    // 发信号禁用删除按钮
    emit enableDeleteTagButton(false);

    return deletedTexts;
}



void MyStringView::updateButtonStyle(QPushButton *button, bool selected) {
    if (selected) {
        button->setStyleSheet("background-color: #3399ff; color: white;");
    } else {
        button->setStyleSheet("background-color: lightgray; color: black;");
    }
}

QStringList MyStringView::getSelectedItems() const {
    QStringList list;
    for (QPushButton *btn : selectedButtons) {
        list << btn->text();
    }
    return list;
}
