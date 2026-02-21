#ifndef TABMODEL_H
#define TABMODEL_H

#include "QString"
#include "ifilter.h"
#include "iorderer.h"
#include <memory>

class TabModel
{
    int _index;
    QString _name;
    std::vector<std::shared_ptr<IFilter>> _filters;
    std::shared_ptr<IOrderer> _orderer;

public:
    TabModel(int index, QString name, std::vector<std::shared_ptr<IFilter>> filters, std::shared_ptr<IOrderer> orderer);

    int getIndex() const;
    QString getName() const;
    const std::vector<std::shared_ptr<IFilter>>& getFilters() const;
    std::shared_ptr<IOrderer> getOrderer() const;

    void setIndex(int index);
    void setName(QString name);
    void setFilters(const std::vector<std::shared_ptr<IFilter>> filters);
    void setOrderer(const std::shared_ptr<IOrderer> orderer);

    TabModel(const TabModel&) = delete;
    TabModel& operator=(const TabModel&) = delete;
    TabModel(TabModel&&) = default;
    TabModel& operator=(TabModel&&) = default;
};

#endif // TABMODEL_H
