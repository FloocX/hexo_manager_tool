#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <qwidget.h>
#include <fstream>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <string>
#include <QDesktopServices>
#include <QTableView>
#include <QProcess>
#include <QtConcurrent/QtConcurrentRun>
#include <QFileSystemModel>
#include <QStandardItem>
#include <QProcess>
#include <QProcessEnvironment>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <windows.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::setConf();

    QTimer::singleShot(0, this, &MainWindow::addListViewToFrames);
    QTimer::singleShot(0, this, &MainWindow::loadFolderTree);
    QTimer::singleShot(0, this, &MainWindow::loadBlogsToManagingView);

    QTimer::singleShot(0, this, &MainWindow::startHexoProcess);

    ui->addTagBtn->setEnabled(false);

    ui->deleteCategoryBtn->setEnabled(false);

    ui->addCategoryBtn->setEnabled(false);

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::on_tabWidget_currentChanged);

    connect(ui->changeHexoBtn, &QPushButton::clicked, this, &MainWindow::on_changeHexoBtn_clicked);

    connect(ui->newCategoryEdit, &QLineEdit::textChanged, this, &MainWindow::onNewCategoriyEditChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//添加展示tags的组件
void MainWindow::addListViewToFrames(){

    MainWindow::getTagsFromPosts();

    QGridLayout *layout = qobject_cast<QGridLayout*>(ui->frame_7->layout());

    if (layout) {
        MainWindow::tags_view = new MyStringView(this);
        MainWindow::tags_view->setStringList(MainWindow::tags, ui->frame_7);
        // qDebug()<<MainWindow::tags;
        connect(MainWindow::tags_view, &MyStringView::enableDeleteTagButton, ui->deleteTagBtn, &QPushButton::setEnabled);
        MainWindow::tags_view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addWidget(MainWindow::tags_view, 1, 0, 1, -1);
    }
}

//从hexo项目中获取tags，更新ui
void MainWindow::getTagsFromPosts(){
    QDir tags_path(MainWindow::hexoProgPath + QString("/public/tags"));
    MainWindow::tags = tags_path.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
}

//检查配置文件
void MainWindow::setConf()
{
    QString confFilePath = "./GenBlogSetting.conf";
    QString hexoPath, bashPath;

    QFile confFile(confFilePath);
    if (confFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&confFile);
        hexoPath = in.readLine().trimmed();
        bashPath = in.readLine().trimmed();
        confFile.close();
    }

    bool needChoose = false;
    if (hexoPath.isEmpty() || !QDir(hexoPath).exists()) {
        needChoose = true;
    }
    if (bashPath.isEmpty() || !QFile::exists(bashPath)) {
        needChoose = true;
    }

    if (needChoose) {
        hexoPath = QFileDialog::getExistingDirectory(this, "选择 Hexo 项目目录");
        if (hexoPath.isEmpty()) return;

        QString bashDir = QFileDialog::getExistingDirectory(this, "选择 Git Bash 的 bin 目录");
        if (bashDir.isEmpty()) return;

        QString tryBashPath = QDir(bashDir).absoluteFilePath("bash.exe");
        if (!QFile::exists(tryBashPath)) {
            QMessageBox::critical(this, "错误", "选中的目录中不包含 bash.exe，请重新尝试。");
            return;
        }
        bashPath = tryBashPath;

        QFile writeFile(confFilePath);
        if (writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&writeFile);
            out << hexoPath << "\n" << bashPath << "\n";
            writeFile.close();
        } else {
            QMessageBox::warning(this, "错误", "无法写入配置文件: " + writeFile.errorString());
            return;
        }
    }

    MainWindow::hexoProgPath = hexoPath;
    MainWindow::bashPath = bashPath;
    ui->HexoProgPathShow->setText("当前hexo目录为 " + hexoPath);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 0) {
        addListViewToFrames();
        loadFolderTree();
    } else if (index == 1) {
        loadBlogsToManagingView();
    }
}

void MainWindow::on_draftBox_stateChanged(int arg1)
{
    if(arg1 == Qt::CheckState::Checked){
        ui->postBox->blockSignals(true);
        ui->postBox->setCheckState(Qt::CheckState::Unchecked);
        ui->postBox->blockSignals(false);
    }
}

void MainWindow::on_postBox_stateChanged(int arg1)
{
    if(arg1 == Qt::CheckState::Checked){
        ui->draftBox->blockSignals(true);
        ui->draftBox->setCheckState(Qt::CheckState::Unchecked);
        ui->draftBox->blockSignals(false);
    }
}

void MainWindow::on_generateBtn_clicked()
{
    QString title = ui->titleEdit->toPlainText().trimmed();
    bool isDraftChecked = ui->draftBox->isChecked();
    bool isPostChecked = ui->postBox->isChecked();


    if (title.isEmpty()) {
        QMessageBox::warning(this, "缺少标题", "请填写博客标题！");
        return;
    }

    if (!isDraftChecked && !isPostChecked) {
        QMessageBox::warning(this, "文章类型未选", "请勾选文章类型！");
        return;
    }

    MainWindow::createNewBlog();
}

//新建博客
void MainWindow::createNewBlog()
{
    QString blog_name = ui->titleEdit->toPlainText().trimmed();
    if (blog_name.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入博客标题");
        return;
    }

    QString blogtype = ui->draftBox->isChecked() ? "draft" : "";
    QString hexoCmd = QString("hexo new %1 \"%2\"").arg(blogtype).arg(blog_name);

    runHexoCommand(hexoCmd);

    QString blogT = (blogtype == "draft") ? "_drafts" : "_posts";
    QString targetFilePath = MainWindow::hexoProgPath + "/source/" + blogT + "/" + blog_name.replace(" ", "-") + ".md";

    // qDebug()<<targetFilePath;

    ui->HexoProgPathShow->setText(targetFilePath);

    QTimer *checkTimer = new QTimer(this);
    checkTimer->setInterval(500); // 每500ms检查一次

    connect(checkTimer, &QTimer::timeout, this, [=]() {
        // qDebug()<<targetFilePath;
        if (QFile::exists(targetFilePath)) {
            checkTimer->stop();  // 停止定时器
            checkTimer->deleteLater(); // 清理定时器


            QMessageBox::information(this, "创建成功", "成功创建文章: \n" + targetFilePath);

            QStringList selectedTags = MainWindow::tags_view->getSelectedItems();
            QStringList selectedCategory = MainWindow::getCategories();
            QString description = ui->descriptionEdit->toPlainText();

            for (QString &tag : selectedTags) {
                if (tag.endsWith("(新)")) {
                    tag.chop(3);
                }
            }
            for (QString &category : selectedCategory) {
                if (category.endsWith("(新)")) {
                    category.chop(3);
                }
            }

            MainWindow::modifyBlogProperties(targetFilePath, selectedTags, selectedCategory, description);
            MainWindow::openMarkdownWithSystemDefault(targetFilePath);
        }
    });

    // 启动检测
    checkTimer->start();

}

//添加tags、categories
void MainWindow::modifyBlogProperties(const QString targetFilePath, const QStringList &tags, const QStringList &categories, const QString &description) {
    QFile file(targetFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "错误", "无法打开文件：" + targetFilePath);
        return;
    }

    QByteArray fileData = file.readAll();
    QString content = QString::fromUtf8(fileData);
    file.close();

    int start = content.indexOf("---");
    int end = content.indexOf("---", start + 3);
    if (start == -1 || end == -1 || end <= start) {
        QMessageBox::warning(this, "格式错误", "Front Matter 格式不正确，无法解析。");
        return;
    }

    QString titleLine;
    QStringList lines = content.mid(start + 3, end - (start + 3)).split('\n');
    for (const QString &line : lines) {
        if (line.trimmed().startsWith("title:")) {
            titleLine = line.trimmed() + "\n";
            break;
        }
    }

    if (titleLine.isEmpty()) {
        QFileInfo info(targetFilePath);
        titleLine = "title: " + info.baseName() + "\n";
    }

    QString frontMatter;
    frontMatter += "---\n";
    frontMatter += titleLine;

    frontMatter += "tags:\n";
    for (const QString &tag : tags) {
        frontMatter += "  - " + tag + "\n";
    }

    frontMatter += "categories:\n";
    for (const QString &cat : categories) {
        frontMatter += "  - " + cat + "\n";
    }

    frontMatter += "description: " + description + "\n";

    if (targetFilePath.contains("/_posts/") || targetFilePath.contains("\\_posts\\")) {
        QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        frontMatter += "date: " + currentTime + "\n";
    }

    frontMatter += "---";

    QString body = content.mid(end + 3);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::warning(this, "错误", "无法写入文件：" + targetFilePath);
        return;
    }

    file.write((frontMatter + body).toUtf8());
    file.close();

    QMessageBox::information(this, "更新成功", "文章头部信息已成功更新！");
}

//创建完成后使用系统默认应用打开文章
void MainWindow::openMarkdownWithSystemDefault(const QString &filePath)
{
    QFileInfo info(filePath);
    if (!info.exists()) {
        QMessageBox::warning(this, "错误", "文件不存在：\n" + filePath);
        return;
    }

    bool success = QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    if (!success) {
        QMessageBox::warning(this, "打开失败", "无法使用系统默认程序打开：\n" + filePath);
    }
}

void MainWindow::on_openDirBtn_clicked()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(MainWindow::hexoProgPath));
}

//从hexo项目获取categories，更新ui
QStringList MainWindow::getCategories(){
    QModelIndex current = ui->categoriesTree->currentIndex();
    if (!current.isValid()) return QStringList();

    QStringList pathParts;

    QModelIndex parent = current.parent();
    while (parent.isValid() && parent.parent().isValid()) {
        pathParts.prepend(parent.data().toString());
        parent = parent.parent();
    }

    pathParts.append(current.data().toString());

    return pathParts;

    // QString fullPath = pathParts.join("/");
    // qDebug() << "选中项路径:" << fullPath;
}

//更新项目目录后重启应用
void restartApplication() {
    QString program = QCoreApplication::applicationFilePath();
    QStringList arguments = QCoreApplication::arguments();

    // 延迟启动
    QTimer::singleShot(100, [=]() {
        QProcess::startDetached(program, arguments);
    });

    QCoreApplication::quit();
}

void MainWindow::on_changeHexoBtn_clicked()
{
    ChooseSettingFIlePath();

    restartApplication();
}

void MainWindow::on_addTagBtn_clicked()
{
    QString tagToAdd = ui->newTagToAddEdit->text();
    MainWindow::new_tags.append(tagToAdd);

    MainWindow::tags_view->addStringList(tagToAdd, ui->frame_7);

    ui->addTagBtn->setEnabled(false);

    MainWindow::addedTags.append(tagToAdd);

}

void MainWindow::on_deleteTagBtn_clicked()
{
    QStringList removed = MainWindow::tags_view->deleteSelectedNewTags();

    for (const QString &tag : removed) {
        addedTags.removeAll(tag);
    }

    // qDebug() << "删除的 tags：" << removed;
    // qDebug() << "剩余的 tags：" << addedTags;
}

//加载categories
void MainWindow::loadFolderTree() {

    QString rootPath = MainWindow::hexoProgPath + QString("/public/categories");

    QStandardItemModel *model = new QStandardItemModel(this);
    QStandardItem *rootItem = new QStandardItem(QFileInfo(rootPath).fileName());
    model->appendRow(rootItem);

    buildTreeRecursive(rootItem, rootPath);

    ui->categoriesTree->setModel(model);
    ui->categoriesTree->expandAll();
    ui->categoriesTree->setHeaderHidden(true);

    connect(ui->categoriesTree->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onCategorySelectionChanged);

}

void MainWindow::on_newTagToAddEdit_textChanged(const QString &arg1)
{
    // qDebug()<<arg1;
    if(arg1.isNull() || arg1.length() == 0){
        // qDebug()<<"string is null";
        ui->addTagBtn->setEnabled(false);
    }else{
        ui->addTagBtn->setEnabled(true);
    }
}

void MainWindow::buildTreeRecursive(QStandardItem *parentItem, const QString &path) {
    QDir dir(path);
    QFileInfoList entries = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

    for (const QFileInfo &entry : entries) {
        QStandardItem *item = new QStandardItem(entry.fileName());
        parentItem->appendRow(item);

        buildTreeRecursive(item, entry.absoluteFilePath());
    }
}

void MainWindow::onCategorySelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{

    // qDebug()<<"selected tree item changed";
    QModelIndexList indexes = selected.indexes();
    if (!indexes.isEmpty()) {
        QModelIndex current = indexes.first();

        bool isNew = current.data(Qt::UserRole + 1).toBool();
        // qDebug()<<current.data();

        if (isNew) {
            ui->deleteCategoryBtn->setEnabled(true);
        } else {
            ui->deleteCategoryBtn->setEnabled(false);
        }
    }
}

void MainWindow::on_addCategoryBtn_clicked()
{
    QModelIndex current = ui->categoriesTree->currentIndex();

    QString newText = ui->newCategoryEdit->text().trimmed();

    QString displayText = newText + " (新)";

    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(ui->categoriesTree->model());
    if (!model) return;

    QStandardItem *parentItem = model->itemFromIndex(current);
    if (!parentItem) return;

    for (int i = 0; i < parentItem->rowCount(); ++i) {
        QString childText = parentItem->child(i)->text();
        if (childText == displayText || childText == newText) {
            QMessageBox::warning(this, "提示", "该分类已存在！");
            return;
        }
    }

    QStandardItem *newItem = new QStandardItem(displayText);
    newItem->setData(true, Qt::UserRole + 1);
    parentItem->appendRow(newItem);

    ui->categoriesTree->expand(current);

    ui->newCategoryEdit->clear();
}

void MainWindow::on_deleteCategoryBtn_clicked()
{
    QModelIndex current = ui->categoriesTree->currentIndex();
    if (!current.isValid()) return;

    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(ui->categoriesTree->model());
    if (!model) return;

    QStandardItem *item = model->itemFromIndex(current);
    if (!item) return;

    QStandardItem *parent = item->parent();

    if (parent) {
        parent->removeRow(item->row());
    } else {
        model->removeRow(item->row());
    }
}

void MainWindow::onNewCategoriyEditChanged(const QString &arg1){
    if(arg1.isNull() || arg1 == ""){
        ui->addCategoryBtn->setEnabled(false);
    }else{
        ui->addCategoryBtn->setEnabled(true);
    }
}

//加载所有文章到管理界面
void MainWindow::loadBlogsToManagingView() {
    if (MainWindow::hexoProgPath.isEmpty())
        return;

    QString postsPath = MainWindow::hexoProgPath + "/source/_posts";
    QString draftsPath = MainWindow::hexoProgPath + "/source/_drafts";

    ui->postsList->clear();
    ui->draftsList->clear();

    QDir postsDir(postsPath);
    QFileInfoList postsFiles = postsDir.entryInfoList(QStringList() << "*.md", QDir::Files);
    for (const QFileInfo &fileInfo : postsFiles) {
        QListWidgetItem *item = new QListWidgetItem(fileInfo.fileName().replace(".md", ""));
        item->setData(Qt::UserRole, fileInfo.absoluteFilePath());
        ui->postsList->addItem(item);
    }

    QDir draftsDir(draftsPath);
    QFileInfoList draftsFiles = draftsDir.entryInfoList(QStringList() << "*.md", QDir::Files);
    for (const QFileInfo &fileInfo : draftsFiles) {
        QListWidgetItem *item = new QListWidgetItem(fileInfo.fileName().replace(".md", ""));
        item->setData(Qt::UserRole, fileInfo.absoluteFilePath());
        ui->draftsList->addItem(item);
    }

    connect(ui->postsList, &QListWidget::itemDoubleClicked, this, &MainWindow::openFileFromItem);
    connect(ui->draftsList, &QListWidget::itemDoubleClicked, this, &MainWindow::openFileFromItem);
}

//实现双击打开文章
void MainWindow::openFileFromItem(QListWidgetItem *item) {
    QString filePath = item->data(Qt::UserRole).toString();
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

//程序启动时，启动一个线程用来执行hexo命令
void MainWindow::startHexoProcess()
{
    QString bashPath;
    QString confFilePath = "./GenBlogSetting.conf";

    QFile confFile(confFilePath);
    if (confFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&confFile);
        QString line1 = in.readLine(); // hexoProgPath
        QString line2 = in.readLine(); // bashPath
        if (!line2.isEmpty()) {
            bashPath = line2.trimmed();
        }
        confFile.close();
    }

    if (bashPath.isEmpty()) {
        QMessageBox::information(this, "Git Bash 未找到", "系统中未检测到 Git Bash，请手动选择包含 bash.exe 的 Git 安装目录。");
        QString dir = QFileDialog::getExistingDirectory(this, "请选择 Git Bash 的 bin 目录（包含 bash.exe）");
        if (dir.isEmpty()) return;

        QString tryPath = QDir(dir).absoluteFilePath("bash.exe");
        if (!QFile::exists(tryPath)) {
            QMessageBox::critical(this, "错误", "选中的目录中不包含 bash.exe，请重新尝试。");
            return;
        }
        bashPath = tryPath;

        QFile outFile(confFilePath);
        if (outFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&outFile);
            out << bashPath << "\n";
            outFile.close();
        } else {
            qDebug() << "配置文件写入失败:" << outFile.errorString();
        }
    }

    hexoProcess = new QProcess(this);
    hexoProcess->setProgram(bashPath);
    hexoProcess->setProcessChannelMode(QProcess::MergedChannels);
    hexoProcess->start();

    if (!hexoProcess->waitForStarted()) {
        QMessageBox::critical(this, "错误", "Git Bash 启动失败！");
        return;
    }

    QString cdCmd = QString("cd \"%1\"\n").arg(MainWindow::hexoProgPath);
    hexoProcess->write(cdCmd.toUtf8());

    connect(hexoProcess, &QProcess::readyReadStandardOutput, [=]() {
        QByteArray out = hexoProcess->readAllStandardOutput();
        qDebug() << "[BASH输出] " << out;
    });


    MainWindow::addListViewToFrames();
    MainWindow::loadFolderTree();
    MainWindow::loadBlogsToManagingView();
}

//执行hexo命令
void MainWindow::runHexoCommand(const QString& command)
{
    if (!hexoProcess || hexoProcess->state() != QProcess::Running) {
        QMessageBox::warning(this, "错误", "Git Bash 进程未启动！");
        return;
    }

    QString cmd = command + "\n";
    hexoProcess->write(cmd.toUtf8());
}

void MainWindow::on_hexo_delete_btn_clicked()
{
    QList<QListWidgetItem*> currentItems;

    if (ui->postsList->hasFocus()) {
        currentItems = ui->postsList->selectedItems();
    } else if (ui->draftsList->hasFocus()) {
        currentItems = ui->draftsList->selectedItems();
    }

    if (currentItems.empty()) {
        QMessageBox::warning(this, "提示", "请先选择要删除的文章！");
        return;
    }

    for(QListWidgetItem * currentItem : currentItems){
        QString filePath = currentItem->data(Qt::UserRole).toString();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "确认删除",
                                      QString("确定要删除这篇文章吗？\n\n%1").arg(filePath),
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply != QMessageBox::Yes)
            return;

        QFile file(filePath);
        if (!file.exists()) {
            QMessageBox::warning(this, "错误", "文件不存在，无法删除！");
            return;
        }

        if (!file.remove()) {
            QMessageBox::critical(this, "错误", "删除文件失败！");
            return;
        }

    }

    loadBlogsToManagingView();
}

void MainWindow::on_hexo_publish_btn_clicked()
{
    QListWidgetItem *currentItem = ui->draftsList->currentItem();

    if (!currentItem) {
        QMessageBox::warning(this, "提示", "请先在草稿列表中选择要发布的文章！");
        return;
    }

    QString draftName = currentItem->text();

    QString command = QString("hexo publish \"%1\"").arg(draftName);

    QProcess process;
    process.setWorkingDirectory(MainWindow::hexoProgPath);
    process.start(command);
    process.waitForFinished(-1);

    QString stdOutput = process.readAllStandardOutput();
    QString errOutput = process.readAllStandardError();

    if (!errOutput.isEmpty()) {
        QMessageBox::warning(this, "错误", "发布失败:\n" + errOutput);
        return;
    }

    loadBlogsToManagingView();

    QMessageBox::information(this, "成功", "发布成功:\n" + stdOutput);
}

void MainWindow::on_hexo_clean_btn_clicked()
{
    runHexoCommand("hexo clean");
    QMessageBox::information(this, "清理完成", "已执行 hexo clean。");
}

void MainWindow::on_hexo_generate_btn_clicked()
{
    runHexoCommand("hexo generate");
    QMessageBox::information(this, "生成完成", "已执行 hexo generate（生成静态文件）。");
}

//实现终止hexo server的函数，未实现
void MainWindow::openCMDWithPortCommand() {
    QString command = QString(
                          "for /f \"tokens=5\" %a in ('netstat -ano ^| find \":%1\" ^| find \"LISTENING\"') do taskkill /PID %a /F"
                          ).arg(hexo_server_port);

    QString fullCmd = QString("cmd.exe /K \"%1 & echo. & echo 执行完毕。 & pause\"").arg(command);

    QProcess::startDetached(fullCmd);
}

//重新选择路径
void MainWindow::ChooseSettingFIlePath()
{
    QString hexoPath = QFileDialog::getExistingDirectory(this, "请选择 Hexo 项目目录");
    if (hexoPath.isEmpty()) return;

    QMessageBox::information(this, "请选择 Git Bash 目录", "请选择包含 bash.exe 的 Git Bash bin 目录。");
    QString gitBashDir = QFileDialog::getExistingDirectory(this, "请选择 Git Bash 的 bin 目录");
    if (gitBashDir.isEmpty()) return;

    QString bashExePath = QDir(gitBashDir).absoluteFilePath("bash.exe");
    if (!QFile::exists(bashExePath)) {
        QMessageBox::critical(this, "错误", "选中的目录中不包含 bash.exe，请重新尝试。");
        return;
    }

    QString confFilePath = "./GenBlogSetting.conf";
    QFile confFile(confFilePath);
    if (!confFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法写入配置文件: " + confFile.errorString());
        return;
    }

    QTextStream out(&confFile);
    out << hexoPath << "\n" << bashExePath << "\n";
    confFile.close();

    MainWindow::hexoProgPath = hexoPath;
    MainWindow::bashPath = bashExePath;

    ui->HexoProgPathShow->setText("当前hexo目录为 " + MainWindow::hexoProgPath);

    QMessageBox::information(this, "成功", "配置已更新并保存。");
}

void MainWindow::on_hexo_server_btn_clicked()
{
    QString port = "4000";

    if (isHexoServerRunning) {
        openCMDWithPortCommand();
        isHexoServerRunning = false;
        return;
    }

    QString indexJsPath = MainWindow::hexoProgPath + "/node_modules/hexo-server/index.js";
    QFile jsFile(indexJsPath);
    if (jsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&jsFile);
        QRegularExpression portRegex(R"(port\s*:\s*(\d+))");

        while (!in.atEnd()) {
            QString line = in.readLine();
            QRegularExpressionMatch match = portRegex.match(line);
            if (match.hasMatch()) {
                port = match.captured(1);
                hexo_server_port = port;
                break;
            }
        }
        jsFile.close();
    }

    MainWindow::runHexoCommand("hexo server");
    isHexoServerRunning = true;

    QString url = "http://localhost:" + port + "/";
    QMessageBox::information(this, "本地服务器启动中", "3 秒后将打开浏览器预览：" + url + "\n再次点击后，退出程序会关闭服务。");

    QTimer::singleShot(3000, this, [url]() {
        QDesktopServices::openUrl(QUrl(url));
    });
}

void MainWindow::on_hexo_deploy_btn_clicked()
{
    runHexoCommand("hexo deploy");
    QMessageBox::information(this, "部署完成", "已执行 hexo deploy（部署到远程）。");
}
