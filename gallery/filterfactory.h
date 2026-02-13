#ifndef FILTERFACTORY_H
#define FILTERFACTORY_H

#include "ifilter.h"
#include "qjsonobject.h"
#include <memory.h>

class FilterFactory
{
public:
    FilterFactory();
    std::unique_ptr<IFilter> parse(QJsonObject jsonValues);
};

#endif // FILTERFACTORY_H
