#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QMainWindow>
#include <QListWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void listFiles(const QString &path);
    QListWidget *fileListWidget;
};

#endif // CONTROLLER_H
