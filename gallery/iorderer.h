#ifndef IORDERER_H
#define IORDERER_H

#include "imagemodel.h"
#include "qjsonobject.h"

enum AvailableOrderers {
    DEFAULT_ORDERER
};

struct IOrderer {
public:
    virtual ~IOrderer() = default;
    virtual std::vector<ImageModel> order(std::vector<ImageModel> images) = 0;
    virtual AvailableOrderers id() = 0;
    virtual QJsonObject serialize() = 0;
};

#endif // IORDERER_H
