#include "ordererfactory.h"
#include "defaultorderer.cpp"
#include "olderfirstorderer.cpp"
#include "lastmodifiedorderer.cpp"
#include "scoreorderer.cpp"

OrdererFactory::OrdererFactory() {}

std::shared_ptr<IOrderer> OrdererFactory::parse(QJsonObject json) {
    QString filterIDString = json["id"].toString();

    if (filterIDString == "DEFAULT_ORDERER") {
        return std::shared_ptr<IOrderer>(new DefaultOrderer());
    } else if (filterIDString == "OLDER_FIRST_ORDERER") {
        return std::shared_ptr<IOrderer>(new OlderFirstOrderer());
    } else if (filterIDString == "LAST_MODIFICATION_FIRST") {
        return std::shared_ptr<IOrderer>(new LastModificationOrderer());
    } else if (filterIDString == "SCORE_ORDERED") {
        return std::shared_ptr<IOrderer>(new ScoreOrderer());
    }
    else {
        throw "Orderer id not recognized";
    }
}
