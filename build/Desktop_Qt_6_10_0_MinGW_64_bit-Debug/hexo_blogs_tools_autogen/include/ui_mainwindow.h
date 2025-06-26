/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *generateBlogTab;
    QGridLayout *gridLayout_3;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QFrame *frame_2;
    QGridLayout *gridLayout_7;
    QCheckBox *draftBox;
    QCheckBox *postBox;
    QFrame *frame_3;
    QGridLayout *gridLayout_4;
    QFrame *frame_5;
    QGridLayout *gridLayout_5;
    QLineEdit *titleShow;
    QTextEdit *titleEdit;
    QFrame *frame_6;
    QGridLayout *gridLayout_6;
    QLineEdit *descriptionShow;
    QTextEdit *descriptionEdit;
    QFrame *frame_7;
    QGridLayout *gridLayout_8;
    QPushButton *addTagBtn;
    QPushButton *deleteTagBtn;
    QLineEdit *newTagToAddEdit;
    QLineEdit *tagsShow;
    QFrame *frame_8;
    QGridLayout *gridLayout_9;
    QPushButton *deleteCategoryBtn;
    QLineEdit *categoriesShow;
    QPushButton *addCategoryBtn;
    QLineEdit *newCategoryEdit;
    QTreeView *categoriesTree;
    QFrame *frame_4;
    QGridLayout *gridLayout_10;
    QLineEdit *HexoProgPathShow;
    QPushButton *generateBtn;
    QPushButton *changeHexoBtn;
    QPushButton *openDirBtn;
    QWidget *managingBlogTab;
    QVBoxLayout *verticalLayout;
    QFrame *frame_9;
    QGridLayout *gridLayout_11;
    QFrame *drafft_frame;
    QGridLayout *gridLayout_14;
    QLineEdit *lineEdit_2;
    QListWidget *draftsList;
    QFrame *post_frame;
    QGridLayout *gridLayout_13;
    QLineEdit *lineEdit;
    QListWidget *postsList;
    QFrame *btn_frame;
    QGridLayout *gridLayout_12;
    QPushButton *hexo_generate_btn;
    QPushButton *hexo_publish_btn;
    QPushButton *hexo_clean_btn;
    QPushButton *hexo_server_btn;
    QPushButton *hexo_deploy_btn;
    QPushButton *hexo_delete_btn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(714, 564);
        QIcon icon;
        icon.addFile(QString::fromUtf8("resources/favicon.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        generateBlogTab = new QWidget();
        generateBlogTab->setObjectName("generateBlogTab");
        gridLayout_3 = new QGridLayout(generateBlogTab);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(generateBlogTab);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_7 = new QGridLayout(frame_2);
        gridLayout_7->setObjectName("gridLayout_7");
        draftBox = new QCheckBox(frame_2);
        draftBox->setObjectName("draftBox");

        gridLayout_7->addWidget(draftBox, 0, 0, 1, 1);

        postBox = new QCheckBox(frame_2);
        postBox->setObjectName("postBox");

        gridLayout_7->addWidget(postBox, 0, 1, 1, 1);


        gridLayout_2->addWidget(frame_2, 0, 0, 1, 1);

        frame_3 = new QFrame(frame);
        frame_3->setObjectName("frame_3");
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_4 = new QGridLayout(frame_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        frame_5 = new QFrame(frame_3);
        frame_5->setObjectName("frame_5");
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_5 = new QGridLayout(frame_5);
        gridLayout_5->setSpacing(4);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(4, 0, 4, 0);
        titleShow = new QLineEdit(frame_5);
        titleShow->setObjectName("titleShow");
        titleShow->setStyleSheet(QString::fromUtf8("background:transparent;"));
        titleShow->setReadOnly(true);

        gridLayout_5->addWidget(titleShow, 0, 0, 1, 1);

        titleEdit = new QTextEdit(frame_5);
        titleEdit->setObjectName("titleEdit");
        titleEdit->setMinimumSize(QSize(0, 60));
        titleEdit->setMaximumSize(QSize(16777215, 65));

        gridLayout_5->addWidget(titleEdit, 0, 1, 1, 1);

        gridLayout_5->setColumnStretch(0, 2);
        gridLayout_5->setColumnStretch(1, 5);

        gridLayout_4->addWidget(frame_5, 0, 0, 1, 1);

        frame_6 = new QFrame(frame_3);
        frame_6->setObjectName("frame_6");
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_6 = new QGridLayout(frame_6);
        gridLayout_6->setSpacing(4);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(4, 0, 4, 0);
        descriptionShow = new QLineEdit(frame_6);
        descriptionShow->setObjectName("descriptionShow");
        descriptionShow->setStyleSheet(QString::fromUtf8("background:transparent"));
        descriptionShow->setReadOnly(true);

        gridLayout_6->addWidget(descriptionShow, 0, 0, 1, 1);

        descriptionEdit = new QTextEdit(frame_6);
        descriptionEdit->setObjectName("descriptionEdit");
        descriptionEdit->setMaximumSize(QSize(16777215, 65));

        gridLayout_6->addWidget(descriptionEdit, 0, 1, 1, 1);

        gridLayout_6->setColumnStretch(0, 2);
        gridLayout_6->setColumnStretch(1, 5);

        gridLayout_4->addWidget(frame_6, 0, 1, 1, 1);

        frame_7 = new QFrame(frame_3);
        frame_7->setObjectName("frame_7");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_7->sizePolicy().hasHeightForWidth());
        frame_7->setSizePolicy(sizePolicy);
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_8 = new QGridLayout(frame_7);
        gridLayout_8->setSpacing(4);
        gridLayout_8->setObjectName("gridLayout_8");
        gridLayout_8->setContentsMargins(4, 4, 4, 4);
        addTagBtn = new QPushButton(frame_7);
        addTagBtn->setObjectName("addTagBtn");
        addTagBtn->setMaximumSize(QSize(25, 25));
        addTagBtn->setStyleSheet(QString::fromUtf8("background:transparent"));

        gridLayout_8->addWidget(addTagBtn, 0, 2, 1, 1);

        deleteTagBtn = new QPushButton(frame_7);
        deleteTagBtn->setObjectName("deleteTagBtn");
        deleteTagBtn->setMaximumSize(QSize(25, 25));

        gridLayout_8->addWidget(deleteTagBtn, 0, 3, 1, 1);

        newTagToAddEdit = new QLineEdit(frame_7);
        newTagToAddEdit->setObjectName("newTagToAddEdit");
        newTagToAddEdit->setMinimumSize(QSize(200, 0));
        newTagToAddEdit->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_8->addWidget(newTagToAddEdit, 0, 1, 1, 1);

        tagsShow = new QLineEdit(frame_7);
        tagsShow->setObjectName("tagsShow");
        tagsShow->setStyleSheet(QString::fromUtf8("background:transparent"));
        tagsShow->setReadOnly(true);

        gridLayout_8->addWidget(tagsShow, 0, 0, 1, 1);


        gridLayout_4->addWidget(frame_7, 1, 0, 1, 1);

        frame_8 = new QFrame(frame_3);
        frame_8->setObjectName("frame_8");
        frame_8->setFrameShape(QFrame::Shape::StyledPanel);
        frame_8->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_9 = new QGridLayout(frame_8);
        gridLayout_9->setSpacing(4);
        gridLayout_9->setObjectName("gridLayout_9");
        gridLayout_9->setContentsMargins(4, 4, 4, 4);
        deleteCategoryBtn = new QPushButton(frame_8);
        deleteCategoryBtn->setObjectName("deleteCategoryBtn");
        deleteCategoryBtn->setMaximumSize(QSize(25, 25));

        gridLayout_9->addWidget(deleteCategoryBtn, 0, 3, 1, 1);

        categoriesShow = new QLineEdit(frame_8);
        categoriesShow->setObjectName("categoriesShow");
        categoriesShow->setStyleSheet(QString::fromUtf8("background:transparent"));
        categoriesShow->setReadOnly(true);

        gridLayout_9->addWidget(categoriesShow, 0, 0, 1, 1);

        addCategoryBtn = new QPushButton(frame_8);
        addCategoryBtn->setObjectName("addCategoryBtn");
        addCategoryBtn->setMaximumSize(QSize(25, 25));

        gridLayout_9->addWidget(addCategoryBtn, 0, 2, 1, 1);

        newCategoryEdit = new QLineEdit(frame_8);
        newCategoryEdit->setObjectName("newCategoryEdit");
        newCategoryEdit->setMinimumSize(QSize(200, 0));

        gridLayout_9->addWidget(newCategoryEdit, 0, 1, 1, 1);

        categoriesTree = new QTreeView(frame_8);
        categoriesTree->setObjectName("categoriesTree");

        gridLayout_9->addWidget(categoriesTree, 1, 0, 1, 4);


        gridLayout_4->addWidget(frame_8, 1, 1, 1, 1);

        gridLayout_4->setRowStretch(0, 2);
        gridLayout_4->setRowStretch(1, 5);
        gridLayout_4->setColumnStretch(0, 1);
        gridLayout_4->setColumnStretch(1, 1);

        gridLayout_2->addWidget(frame_3, 1, 0, 1, 1);

        frame_4 = new QFrame(frame);
        frame_4->setObjectName("frame_4");
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_10 = new QGridLayout(frame_4);
        gridLayout_10->setObjectName("gridLayout_10");
        gridLayout_10->setHorizontalSpacing(10);
        HexoProgPathShow = new QLineEdit(frame_4);
        HexoProgPathShow->setObjectName("HexoProgPathShow");
        HexoProgPathShow->setMinimumSize(QSize(0, 40));
        HexoProgPathShow->setMaximumSize(QSize(16777215, 16777215));
        HexoProgPathShow->setStyleSheet(QString::fromUtf8("font:14px"));
        HexoProgPathShow->setReadOnly(true);

        gridLayout_10->addWidget(HexoProgPathShow, 0, 0, 1, 1);

        generateBtn = new QPushButton(frame_4);
        generateBtn->setObjectName("generateBtn");

        gridLayout_10->addWidget(generateBtn, 0, 3, 1, 1);

        changeHexoBtn = new QPushButton(frame_4);
        changeHexoBtn->setObjectName("changeHexoBtn");

        gridLayout_10->addWidget(changeHexoBtn, 0, 2, 1, 1);

        openDirBtn = new QPushButton(frame_4);
        openDirBtn->setObjectName("openDirBtn");

        gridLayout_10->addWidget(openDirBtn, 0, 1, 1, 1);


        gridLayout_2->addWidget(frame_4, 2, 0, 1, 1);

        gridLayout_2->setRowStretch(0, 2);
        gridLayout_2->setRowStretch(1, 9);
        gridLayout_2->setRowStretch(2, 2);

        gridLayout_3->addWidget(frame, 0, 0, 1, 1);

        tabWidget->addTab(generateBlogTab, QString());
        managingBlogTab = new QWidget();
        managingBlogTab->setObjectName("managingBlogTab");
        verticalLayout = new QVBoxLayout(managingBlogTab);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame_9 = new QFrame(managingBlogTab);
        frame_9->setObjectName("frame_9");
        frame_9->setFrameShape(QFrame::Shape::StyledPanel);
        frame_9->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_11 = new QGridLayout(frame_9);
        gridLayout_11->setObjectName("gridLayout_11");
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        drafft_frame = new QFrame(frame_9);
        drafft_frame->setObjectName("drafft_frame");
        drafft_frame->setFrameShape(QFrame::Shape::StyledPanel);
        drafft_frame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_14 = new QGridLayout(drafft_frame);
        gridLayout_14->setObjectName("gridLayout_14");
        gridLayout_14->setContentsMargins(4, 4, 4, 4);
        lineEdit_2 = new QLineEdit(drafft_frame);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setMinimumSize(QSize(0, 0));
        lineEdit_2->setMaximumSize(QSize(120, 16777215));
        lineEdit_2->setStyleSheet(QString::fromUtf8("background:transparent;"));

        gridLayout_14->addWidget(lineEdit_2, 0, 0, 1, 1);

        draftsList = new QListWidget(drafft_frame);
        draftsList->setObjectName("draftsList");

        gridLayout_14->addWidget(draftsList, 1, 0, 1, 1);


        gridLayout_11->addWidget(drafft_frame, 0, 1, 1, 1);

        post_frame = new QFrame(frame_9);
        post_frame->setObjectName("post_frame");
        post_frame->setFrameShape(QFrame::Shape::StyledPanel);
        post_frame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_13 = new QGridLayout(post_frame);
        gridLayout_13->setObjectName("gridLayout_13");
        gridLayout_13->setContentsMargins(4, 4, 4, 4);
        lineEdit = new QLineEdit(post_frame);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMaximumSize(QSize(120, 16777215));
        lineEdit->setStyleSheet(QString::fromUtf8("background:transparent;"));

        gridLayout_13->addWidget(lineEdit, 0, 0, 1, 1);

        postsList = new QListWidget(post_frame);
        postsList->setObjectName("postsList");

        gridLayout_13->addWidget(postsList, 1, 0, 1, 1);


        gridLayout_11->addWidget(post_frame, 0, 0, 1, 1);

        btn_frame = new QFrame(frame_9);
        btn_frame->setObjectName("btn_frame");
        btn_frame->setFrameShape(QFrame::Shape::StyledPanel);
        btn_frame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_12 = new QGridLayout(btn_frame);
        gridLayout_12->setObjectName("gridLayout_12");
        gridLayout_12->setHorizontalSpacing(100);
        hexo_generate_btn = new QPushButton(btn_frame);
        hexo_generate_btn->setObjectName("hexo_generate_btn");

        gridLayout_12->addWidget(hexo_generate_btn, 0, 0, 1, 1);

        hexo_publish_btn = new QPushButton(btn_frame);
        hexo_publish_btn->setObjectName("hexo_publish_btn");

        gridLayout_12->addWidget(hexo_publish_btn, 1, 0, 1, 1);

        hexo_clean_btn = new QPushButton(btn_frame);
        hexo_clean_btn->setObjectName("hexo_clean_btn");

        gridLayout_12->addWidget(hexo_clean_btn, 0, 1, 1, 1);

        hexo_server_btn = new QPushButton(btn_frame);
        hexo_server_btn->setObjectName("hexo_server_btn");

        gridLayout_12->addWidget(hexo_server_btn, 0, 2, 1, 1);

        hexo_deploy_btn = new QPushButton(btn_frame);
        hexo_deploy_btn->setObjectName("hexo_deploy_btn");

        gridLayout_12->addWidget(hexo_deploy_btn, 1, 1, 1, 1);

        hexo_delete_btn = new QPushButton(btn_frame);
        hexo_delete_btn->setObjectName("hexo_delete_btn");

        gridLayout_12->addWidget(hexo_delete_btn, 1, 2, 1, 1);


        gridLayout_11->addWidget(btn_frame, 1, 0, 1, 2);

        gridLayout_11->setRowStretch(0, 10);
        gridLayout_11->setColumnStretch(0, 1);
        gridLayout_11->setColumnStretch(1, 1);

        verticalLayout->addWidget(frame_9);

        tabWidget->addTab(managingBlogTab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 714, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "hexo\345\215\232\345\256\242\347\256\241\347\220\206GUI By Flooc", nullptr));
#if QT_CONFIG(tooltip)
        draftBox->setToolTip(QCoreApplication::translate("MainWindow", "draft", nullptr));
#endif // QT_CONFIG(tooltip)
        draftBox->setText(QCoreApplication::translate("MainWindow", "\350\215\211\347\250\277", nullptr));
#if QT_CONFIG(tooltip)
        postBox->setToolTip(QCoreApplication::translate("MainWindow", "post", nullptr));
#endif // QT_CONFIG(tooltip)
        postBox->setText(QCoreApplication::translate("MainWindow", "\346\226\207\347\253\240", nullptr));
#if QT_CONFIG(tooltip)
        titleShow->setToolTip(QCoreApplication::translate("MainWindow", "title", nullptr));
#endif // QT_CONFIG(tooltip)
        titleShow->setText(QCoreApplication::translate("MainWindow", "\346\240\207\351\242\230\357\274\232", nullptr));
#if QT_CONFIG(tooltip)
        descriptionShow->setToolTip(QCoreApplication::translate("MainWindow", "description", nullptr));
#endif // QT_CONFIG(tooltip)
        descriptionShow->setText(QCoreApplication::translate("MainWindow", "\346\217\217\350\277\260\357\274\232", nullptr));
        addTagBtn->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        deleteTagBtn->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
#if QT_CONFIG(tooltip)
        tagsShow->setToolTip(QCoreApplication::translate("MainWindow", "tags", nullptr));
#endif // QT_CONFIG(tooltip)
        tagsShow->setText(QCoreApplication::translate("MainWindow", "\346\240\207\347\255\276\357\274\232", nullptr));
        deleteCategoryBtn->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
#if QT_CONFIG(tooltip)
        categoriesShow->setToolTip(QCoreApplication::translate("MainWindow", "tags", nullptr));
#endif // QT_CONFIG(tooltip)
        categoriesShow->setText(QCoreApplication::translate("MainWindow", "\345\210\206\347\261\273\357\274\232", nullptr));
        addCategoryBtn->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        HexoProgPathShow->setText(QString());
        generateBtn->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272", nullptr));
        changeHexoBtn->setText(QCoreApplication::translate("MainWindow", "\346\233\264\346\215\242\347\233\256\345\275\225", nullptr));
        openDirBtn->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\347\233\256\345\275\225", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(generateBlogTab), QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "drafts:", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "posts:", nullptr));
        hexo_generate_btn->setText(QCoreApplication::translate("MainWindow", "hexo g", nullptr));
        hexo_publish_btn->setText(QCoreApplication::translate("MainWindow", "publish(\346\234\252\345\256\214\346\210\220", nullptr));
        hexo_clean_btn->setText(QCoreApplication::translate("MainWindow", "hexo clean", nullptr));
        hexo_server_btn->setText(QCoreApplication::translate("MainWindow", "hexo s(\345\256\214\346\210\220\344\270\200\345\215\212", nullptr));
        hexo_deploy_btn->setText(QCoreApplication::translate("MainWindow", "\351\203\250\347\275\262", nullptr));
        hexo_delete_btn->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244(\346\234\252\345\256\214\346\210\220", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(managingBlogTab), QCoreApplication::translate("MainWindow", "\347\256\241\347\220\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
