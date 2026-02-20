#include "sidebarempty.h"
#include "starsfilter.cpp"
#include "serializationservice.h"

SideBarEmpty::SideBarEmpty(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::SideBarEmpty)
{
    ui->setupUi(this);

    ui->label->setAlignment(Qt::AlignCenter);

    ui->label->setStyleSheet(R"(
        QLabel {
            font-size: 20px;
            font-weight: 600;
            color: #555555;
        }
    )");

    connect(ui->onestar, &QCheckBox::checkStateChanged, this, [this]() {
        if (_currentTab != nullptr) {
            std::vector<std::shared_ptr<IFilter>> filters = _currentTab->getFilters();
            if (ui->onestar->isChecked()) {
                filters.push_back(std::shared_ptr<IFilter>(new StarsFilter(1)));
            } else {
                filters.erase(std::remove_if(filters.begin(), filters.end(),
                                             [](const std::shared_ptr<IFilter>& f) {
                                                 StarsFilter* sf = dynamic_cast<StarsFilter*>(f.get());
                                                 return sf && sf->getScore() == 1;
                                             }), filters.end());
            }
            _currentTab->setFilters(filters);
            saveAndPushChanges();
        }
    });

    connect(ui->twoStars, &QCheckBox::checkStateChanged, this, [this]() {
        if (_currentTab != nullptr) {
            std::vector<std::shared_ptr<IFilter>> filters = _currentTab->getFilters();
            if (ui->onestar->isChecked()) {
                filters.push_back(std::shared_ptr<IFilter>(new StarsFilter(2)));
            } else {
                filters.erase(std::remove_if(filters.begin(), filters.end(),
                                             [](const std::shared_ptr<IFilter>& f) {
                                                 StarsFilter* sf = dynamic_cast<StarsFilter*>(f.get());
                                                 return sf && sf->getScore() == 2;
                                             }), filters.end());
            }
            _currentTab->setFilters(filters);
            saveAndPushChanges();
        }
    });

    connect(ui->threestars, &QCheckBox::checkStateChanged, this, [this]() {
        if (_currentTab != nullptr) {
            std::vector<std::shared_ptr<IFilter>> filters = _currentTab->getFilters();
            if (ui->onestar->isChecked()) {
                filters.push_back(std::shared_ptr<IFilter>(new StarsFilter(3)));
            } else {
                filters.erase(std::remove_if(filters.begin(), filters.end(),
                                             [](const std::shared_ptr<IFilter>& f) {
                                                 StarsFilter* sf = dynamic_cast<StarsFilter*>(f.get());
                                                 return sf && sf->getScore() == 3;
                                             }), filters.end());
            }
            _currentTab->setFilters(filters);
            saveAndPushChanges();
        }
    });

    connect(ui->fourstars, &QCheckBox::checkStateChanged, this, [this]() {
        if (_currentTab != nullptr) {
            std::vector<std::shared_ptr<IFilter>> filters = _currentTab->getFilters();
            if (ui->onestar->isChecked()) {
                filters.push_back(std::shared_ptr<IFilter>(new StarsFilter(4)));
            } else {
                filters.erase(std::remove_if(filters.begin(), filters.end(),
                                             [](const std::shared_ptr<IFilter>& f) {
                                                 StarsFilter* sf = dynamic_cast<StarsFilter*>(f.get());
                                                 return sf && sf->getScore() == 4;
                                             }), filters.end());
            }
            _currentTab->setFilters(filters);
            saveAndPushChanges();
        }
    });

    connect(ui->fivestars, &QCheckBox::checkStateChanged, this, [this]() {
        if (_currentTab != nullptr) {
            std::vector<std::shared_ptr<IFilter>> filters = _currentTab->getFilters();
            if (ui->onestar->isChecked()) {
                filters.push_back(std::shared_ptr<IFilter>(new StarsFilter(5)));
            } else {
                filters.erase(std::remove_if(filters.begin(), filters.end(),
                                             [](const std::shared_ptr<IFilter>& f) {
                                                 StarsFilter* sf = dynamic_cast<StarsFilter*>(f.get());
                                                 return sf && sf->getScore() == 5;
                                             }), filters.end());
            }
            _currentTab->setFilters(filters);
            saveAndPushChanges();
        }
    });
}

SideBarEmpty::~SideBarEmpty()
{
    delete ui;
}

void SideBarEmpty::setCurrentTab(TabModel* tab)
{
    _currentTab = tab;
}

void SideBarEmpty::refreshModel()
{
    // TODO: à implémenter
}

void SideBarEmpty::saveAndPushChanges() {
    SerializationService service;
    service.serializeTabModel(*_currentTab);
    emit onModelChanged();
}
