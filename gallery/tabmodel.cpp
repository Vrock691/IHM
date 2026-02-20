#include "tabmodel.h"

TabModel::TabModel(
    int index,
    QString name,
    std::vector<std::shared_ptr<IFilter>> filters,
    std::shared_ptr<IOrderer> orderer
    ) :
    _index(index),
    _name(name),
    _filters(filters),
    _orderer(orderer)
{}

int TabModel::getIndex() const { return _index; }
QString TabModel::getName() const { return _name; }
const std::vector<std::shared_ptr<IFilter>>& TabModel::getFilters() const { return _filters; }
std::shared_ptr<IOrderer> TabModel::getOrderer() const { return _orderer; }

void TabModel::setIndex(int index) { _index = index; }
void TabModel::setName(QString name) { _name = name; }
void TabModel::setFilters(std::vector<std::shared_ptr<IFilter>> filters) { _filters = filters; }
void TabModel::setOrderer(std::shared_ptr<IOrderer> orderer) { _orderer = orderer; }
