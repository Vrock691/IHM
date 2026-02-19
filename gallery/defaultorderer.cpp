#include "iorderer.h"

class DefaultOrderer : public IOrderer {
public:
    std::vector<ImageModel> order(std::vector<ImageModel> images) override {
        return images;
    }

    AvailableOrderers id() override {
        return DEFAULT_ORDERER;
    }

    QJsonObject serialize() override {
        QJsonObject json;
        json["id"] = "DEFAULT_ORDERER";
        return json;
    }
};
