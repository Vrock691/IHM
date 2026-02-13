#include "ordererfactory.h"
#include "defaultorderer.cpp"

OrdererFactory::OrdererFactory() {}

std::unique_ptr<IOrderer> OrdererFactory::parse(QJsonObject json) {
    QString filterIDString = json["id"].toString();

    if (filterIDString == "DEFAULT_ORDERER") {
        return std::unique_ptr<IOrderer>(new DefaultOrderer());
    } // Insérer les prochaine instanciations de tri ici
    else {
        throw "Orderer id not recognized";
    }
}
