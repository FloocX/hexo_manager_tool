#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QItemSelection>
#include <QListWidgetItem>
#include <QStandardItem>
#include <QProcess>
#include "MyStringView.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_draftBox_stateChanged(int arg1);

    void on_postBox_stateChanged(int arg1);

    void on_generateBtn_clicked();

    void on_openDirBtn_clicked();

    // void onCleearButtonClicked();

    void on_changeHexoBtn_clicked();

    void on_addTagBtn_clicked();

    void on_deleteTagBtn_clicked();

    void on_newTagToAddEdit_textChanged(const QString &arg1);

    void buildTreeRecursive(QStandardItem *parentItem, const QString &path);

    void onCategorySelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    void on_addCategoryBtn_clicked();

    void on_deleteCategoryBtn_clicked();

    void onNewCategoriyEditChanged(const QString &arg1);

    void on_hexo_delete_btn_clicked();

    void on_hexo_deploy_btn_clicked();

    void on_hexo_publish_btn_clicked();

    void on_hexo_server_btn_clicked();

    void on_hexo_clean_btn_clicked();

    void on_hexo_generate_btn_clicked();

private:
    Ui::MainWindow *ui;

    QProcess *hexoProcess = nullptr;

    QString hexoProgPath;

    QStringList tags;

    QStringList new_tags;

    MyStringView* tags_view;

    QStringList addedTags;

    QString hexo_server_port;

    QString bashPath;

    bool isHexoServerRunning = false;

    void setConf();

    void addListViewToFrames();

    void getTagsFromPosts();

    void createNewBlog();

    void modifyBlogProperties(const QString targetFilePath, const QStringList &tags, const QStringList &categories, const QString &description);

    QStringList getCategories();

    void loadFolderTree();

    void openMarkdownWithSystemDefault(const QString &filePath);

    void loadBlogsToManagingView();

    void openFileFromItem(QListWidgetItem *item);

    void startHexoProcess();

    // void stopHexoProcess();

    void openCMDWithPortCommand();

    void runHexoCommand(const QString &cmd);

    void ChooseSettingFIlePath();


};
#endif // MAINWINDOW_H
