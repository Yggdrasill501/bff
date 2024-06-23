#include "controller.h"
#include <QVBoxLayout>
#include <QDir>
#include <QFileIconProvider>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    fileListWidget = new QListWidget(this);
    setCentralWidget(fileListWidget);
    listFiles(QDir::currentPath());
}

void MainWindow::listFiles(const QString &path) {
    QDir dir(path);
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

    QFileInfoList list = dir.entryInfoList();
    fileListWidget->clear();

    QFileIconProvider iconProvider;
    for (const QFileInfo &fileInfo : list) {
        QListWidgetItem *item = new QListWidgetItem(iconProvider.icon(fileInfo), fileInfo.fileName(), fileListWidget);
        fileListWidget->addItem(item);
    }
}
