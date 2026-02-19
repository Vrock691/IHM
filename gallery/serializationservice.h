#include "imagemodel.h"
#include "tabmodel.h"
#include "QString"
#include "QFile"
#include "QStandardPaths"
#include "QDir"
#include "QCryptographicHash"
#include <QJsonArray>

#ifndef SERIALIZATIONSERVICE_H
#define SERIALIZATIONSERVICE_H

class SerializationService
{
public:
    SerializationService();

    void serializeImageModel(ImageModel imageModel);

    void serializeTabModel(const TabModel& tabModel);

    std::vector<ImageModel*> deserializeImageModels();

    std::vector<TabModel*> deserializeTabModels();
private:
    QString getSha1FromString(const QString value);
    Color getColorFromString(const QString value);
    QString colorToString(const Color color);
};

#endif // SERIALIZATIONSERVICE_H
