#include "tabmodel.h"

TabModel::TabModel(
    int index,
    QString name,
    std::vector<std::unique_ptr<IFilter>> filters,
    std::unique_ptr<IOrderer> orderer
    ) :
    _index(index),
    _name(name),
    _filters(std::move(filters)),
    _orderer(std::move(orderer))
{}

int TabModel::getIndex() const { return _index; }
QString TabModel::getName() const { return _name; }
const std::vector<std::unique_ptr<IFilter>>& TabModel::getFilters() const { return _filters; }
IOrderer* TabModel::getOrderer() const { return _orderer.get(); }

void TabModel::setIndex(int index) { _index = index; }
void TabModel::setName(QString name) { _name = name; }
void TabModel::setFilters(std::vector<std::unique_ptr<IFilter>> filters) { _filters = std::move(filters); }
void TabModel::setOrderer(std::unique_ptr<IOrderer> orderer) { _orderer = std::move(orderer); }
