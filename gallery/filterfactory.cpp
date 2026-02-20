#include "filterfactory.h"
#include "defaultfilter.cpp"
#include "starsfilter.cpp"

FilterFactory::FilterFactory() {}

std::shared_ptr<IFilter> FilterFactory::parse(QJsonObject json) {
    QString filterID = json["id"].toString();

    if (filterID == "DEFAULT_FILTER") {
        return std::shared_ptr<IFilter>(new DefaultFilter());
    } else if (filterID == "STARS_FILTER") {
        int value = json["value"].toInt();
        return std::shared_ptr<IFilter>(new StarsFilter(value));
    } else {
        throw "Filter id not recognized";
    }
}
