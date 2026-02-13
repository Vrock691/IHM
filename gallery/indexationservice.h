#ifndef INDEXATIONSERVICE_H
#define INDEXATIONSERVICE_H

#include "imagemodel.h"

#include <QString>
#include <QVector>
#include <QMap>

class IndexationService
{
public:
    IndexationService();
    QVector<ImageModel> indexFiles(const QString &folderPath);
};

#endif // INDEXATIONSERVICE_H
