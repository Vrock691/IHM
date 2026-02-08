#ifndef IFILTER_H
#define IFILTER_H

class IFilter {
    public:
        virtual ~IFilter() = default;
        virtual bool isAcceptable() = 0;
};

#endif // IFILTER_H
