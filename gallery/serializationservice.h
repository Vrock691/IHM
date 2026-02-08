#include "imagemodel.cpp"
#include "tabmodel.cpp"
#include "QString"
#include "QFile"
#include "QStandardPaths"
#include "QDir"
#include "QCryptographicHash"

#ifndef SERIALIZATIONSERVICE_H
#define SERIALIZATIONSERVICE_H

class serializationservice
{
public:
    serializationservice();

    void serializeImageModel(ImageModel imageModel);

    void serializeTabModel(TabModel tabModel);

    ImageModel deserializeImageModels();

    TabModel deserializeTabModels();
private:
    QString getSha1FromString(const QString &value);
};

#endif // SERIALIZATIONSERVICE_H
