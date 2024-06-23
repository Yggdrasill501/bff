#include "icons.h"
#include <QFileIconProvider>

QIcon getIcon(const QFileInfo &fileInfo) {
    QFileIconProvider provider;
    if (fileInfo.isDir()) {
        return QIcon(":/icons/directory.svg");
    } else {
        // You can add more specific file type handling here
        return QIcon(":/icons/file.svg");
    }
}
