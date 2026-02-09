#ifndef IFILTER_H
#define IFILTER_H

#include <QString>

enum AvailableFilters {
    DEFAULT_FILTER
};

class IFilter {
    public:
        virtual ~IFilter() = default;
        virtual bool isAcceptable() = 0;
        virtual AvailableFilters id() = 0;
};

#endif // IFILTER_H
