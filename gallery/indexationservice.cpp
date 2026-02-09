#include "indexationservice.h"
#include <QDir>
#include <QFileInfoList>

IndexationService::IndexationService() {}

QVector<ImageModel> IndexationService::indexFiles(const QString &folderPath)
{
    QVector<ImageModel> models;

    QDir dir(folderPath);
    if (!dir.exists()) return models;

    QStringList filters {"*.jpg", "*.png", "*.jpeg" };

    QFileInfoList files = dir.entryInfoList(filters, QDir::Files);
    for (int i = 0; i < files.size(); i++) {
        const QFileInfo &file = files[i];
        QString path = file.absoluteFilePath();

        models.append(ImageModel(path.toStdString()));

    }

    QFileInfoList subDirs = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < subDirs.size(); i++) {
        const QFileInfo &subDir = subDirs[i];
        models.append(indexFiles(subDir.absoluteFilePath()));
    }

    return models;
}
