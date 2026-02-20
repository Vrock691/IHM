#include "iorderer.h"

class DefaultOrderer : public IOrderer {
public:
    bool orderer(ImageModel* a, ImageModel* b) override {
        Q_UNUSED(a);
        Q_UNUSED(b);
        return true;
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
