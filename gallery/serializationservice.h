#include "imagemodel.cpp"
#include "tabmodel.cpp"

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
};

#endif // SERIALIZATIONSERVICE_H
