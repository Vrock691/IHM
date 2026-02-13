#ifndef ORDERERFACTORY_H
#define ORDERERFACTORY_H

#include "iorderer.h"
#include <memory>
#include <QJsonObject>

class OrdererFactory
{
public:
    OrdererFactory();
    std::unique_ptr<IOrderer> parse(QJsonObject json);
};

#endif // ORDERERFACTORY_H
