#include "ifilter.h"
#include "imagemodel.h"
#include "qjsonobject.h"

class StarsFilter : public IFilter {
public:
    StarsFilter(unsigned int v) {
        value = v;
    }

    bool isAcceptable(ImageModel* model) override {
        if ((int) model->score() == value) {
            return true;
        }
        return false;
    }

    AvailableFilters id() override {
        return STARS_FILTER;
    }

    QJsonObject serialize() override {
        QJsonObject json;
        json["id"] = "STARS_FILTER";
        json["value"] = value;
        return json;
    }

    int getScore() {
        return value;
    }
private:
    int value = 1;
};
