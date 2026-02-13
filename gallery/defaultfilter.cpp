#include "ifilter.h"
#include "qjsonobject.h"

class DefaultFilter : public IFilter {
public:
    bool isAcceptable() override {
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
