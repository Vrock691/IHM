#ifndef TABMODEL_H
#define TABMODEL_H

#include "QString"
#include "ifilter.h"
#include "iorderer.h"

class TabModel
{
    int _index;
    QString _name;
    std::vector<IFilter> _filters;
    IOrderer* _orderer;

public:
    TabModel(int index, QString name, std::vector<IFilter> filters, IOrderer* orderer);

    int getIndex() const;
    QString getName() const;
    std::vector<IFilter> getFilters() const;
    IOrderer getOrderer() const;

    void setIndex(int index);
    void setName(QString name);
    void setFilters(const std::vector<IFilter> filters);
    void setOrderer(const IOrderer orderer);
};

#endif // TABMODEL_H
