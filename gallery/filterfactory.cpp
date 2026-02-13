#include "filterfactory.h"
#include "defaultfilter.cpp"

FilterFactory::FilterFactory() {}

std::unique_ptr<IFilter> FilterFactory::parse(QJsonObject json) {
    QString filterID = json["id"].toString();

    if (filterID == "DEFAULT_FILTER") {
        return std::unique_ptr<IFilter>(new DefaultFilter());
    } // Insérer les prochaine instanciations de filtres ici
    else {
        throw "Filter id not recognized";
    }
}
