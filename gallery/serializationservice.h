#include "imagemodel.cpp"
#include "tabmodel.cpp"
#include "QString"
#include "QFile"
#include "QStandardPaths"
#include "QDir"
#include "QCryptographicHash"
#include <QJsonArray>

#ifndef SERIALIZATIONSERVICE_H
#define SERIALIZATIONSERVICE_H

class serializationservice
{
public:
    serializationservice();

    void serializeImageModel(ImageModel imageModel);

    void serializeTabModel(TabModel tabModel);

    std::vector<ImageModel> deserializeImageModels();

    TabModel deserializeTabModels();
private:
    QString getSha1FromString(const QString value);
    Color getColorFromString(const QString value);
    Feeling getFeelingFromString(const QString value);
};

#endif // SERIALIZATIONSERVICE_H
