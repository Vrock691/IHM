#ifndef INDEXATIONSERVICE_H
#define INDEXATIONSERVICE_H

#include "imagemodel.h"

#include <QString>
#include <QVector>
#include <QMap>
#include <memory>

class IndexationService
{
public:
    IndexationService();
    QVector<ImageModel> indexFiles(const QString &folderPath);

private:
    QMap<QString, std::shared_ptr<ImageModel>> cache;
};

#endif // INDEXATIONSERVICE_H
