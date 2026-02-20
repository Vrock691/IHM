#ifndef IFILTER_H
#define IFILTER_H

#include "imagemodel.h"
#include "qjsonvalue.h"
#include <QString>

enum AvailableFilters {
    DEFAULT_FILTER
};

class IFilter {
    public:
        virtual ~IFilter() = default;
        virtual bool isAcceptable(ImageModel* model) = 0;
        virtual AvailableFilters id() = 0;
        virtual QJsonObject serialize() = 0;
};

#endif // IFILTER_H
