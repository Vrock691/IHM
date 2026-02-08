#include "tabmodel.h"

TabModel::TabModel(int index, QString name, std::vector<IFilter> filters, IOrderer orderer) :
    _index(index), _name(name), _filters(filters), _orderer(orderer) {}

int TabModel::getIndex() const { return this->_index; }
QString TabModel::getName() const { return this->_name; }
std::vector<IFilter> TabModel::getFilters() const { return this->_filters; }
IOrderer TabModel::getOrderer() const { return this->_orderer; }

void TabModel::setIndex(int index) { this->_index = index; }
void TabModel::setName(QString name) { this->_name = name; }
void TabModel::setFilters(const std::vector<IFilter> filters) { this->_filters = filters; }
void TabModel::setOrderer(const IOrderer orderer) { this->_orderer = orderer; }
