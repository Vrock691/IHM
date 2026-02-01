#include "indexationservice.h"
#include <QDir>
#include <QFileInfoList>

IndexationService::IndexationService() {}

QStringList IndexationService::indexFolder(const QString &folderPath)
{
    QStringList imagePaths;
    QDir dir(folderPath);

    QStringList filters;
    filters << "*.jpg" << "*.png" << "*.jpeg";

    QFileInfoList files = dir.entryInfoList(filters, QDir::Files);
    for (const QFileInfo &file : files) {
        imagePaths << file.absoluteFilePath();
    }

    return imagePaths;
}
