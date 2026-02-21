#include "ifilter.h"
#include "imagemodel.h"
#include "qjsonobject.h"

class DefaultFilter : public IFilter {
public:
    bool isAcceptable(ImageModel* model) override {
        return true;
    }

    AvailableFilters id() override {
        return DEFAULT_FILTER;
    }

    QJsonObject serialize() override {
        QJsonObject json;
        json["id"] = "DEFAULT_FILTER";
        return json;
    }
};
