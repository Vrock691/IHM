#ifndef INDEXATIONSERVICE_H
#define INDEXATIONSERVICE_H

#include <QString>
#include <QStringList>

class IndexationService
{
public:
    IndexationService();
    QStringList indexFolder(const QString &folderPath);
};

#endif // INDEXATIONSERVICE_H
