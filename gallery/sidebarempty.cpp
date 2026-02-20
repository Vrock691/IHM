#include "sidebarempty.h"
#include "starsfilter.cpp"
#include "feelingfilter.cpp"
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
        setStarFilter(ui->onestar->isChecked(), 1);
    });
    connect(ui->twoStars, &QCheckBox::checkStateChanged, this, [this]() {
        setStarFilter(ui->twoStars->isChecked(), 2);
    });
    connect(ui->threestars, &QCheckBox::checkStateChanged, this, [this]() {
        setStarFilter(ui->threestars->isChecked(), 3);
    });
    connect(ui->fourstars, &QCheckBox::checkStateChanged, this, [this]() {
        setStarFilter(ui->fourstars->isChecked(), 4);
    });
    connect(ui->fivestars, &QCheckBox::checkStateChanged, this, [this]() {
        setStarFilter(ui->fivestars->isChecked(), 5);
    });

    connect(ui->heureux, &QCheckBox::checkStateChanged, this, [this]() {
        setFeelingFilter(ui->heureux->isChecked(), HAPPY);
    });
    connect(ui->sad, &QCheckBox::checkStateChanged, this, [this]() {
        setFeelingFilter(ui->sad->isChecked(), SAD);
    });
    connect(ui->inspired, &QCheckBox::checkStateChanged, this, [this]() {
        setFeelingFilter(ui->inspired->isChecked(), INSPIRED);
    });
    connect(ui->calm, &QCheckBox::checkStateChanged, this, [this]() {
        setFeelingFilter(ui->calm->isChecked(), CALM);
    });
    connect(ui->excite, &QCheckBox::checkStateChanged, this, [this]() {
        setFeelingFilter(ui->excite->isChecked(), EXCITED);
    });
}

SideBarEmpty::~SideBarEmpty()
{
    delete ui;
}

void SideBarEmpty::setCurrentTab(TabModel* tab)
{
    _currentTab = tab;
    refreshModel();
}

void SideBarEmpty::refreshModel()
{
    if (!_currentTab) {
        qDebug() << "No tab selected";
        return;
    }

    updateStarsCheckboxes();
    updateFeelingsCheckboxes();
}

void SideBarEmpty::saveAndPushChanges()
{
    SerializationService service;
    service.serializeTabModel(*_currentTab);
    emit onModelChanged();
}

void SideBarEmpty::setStarFilter(bool isEnabled, int starAmount)
{
    if (_currentTab == nullptr)
        return;

    std::vector<std::shared_ptr<IFilter>> filters = _currentTab->getFilters();
    if (isEnabled) {
        filters.push_back(std::shared_ptr<IFilter>(new StarsFilter(starAmount)));
    } else {
        filters.erase(std::remove_if(filters.begin(), filters.end(),
                                     [=](const std::shared_ptr<IFilter>& f) {
                                         StarsFilter* sf = dynamic_cast<StarsFilter*>(f.get());
                                         return sf && sf->getScore() == starAmount;
                                     }), filters.end());
    }
    _currentTab->setFilters(filters);
    saveAndPushChanges();
}

void SideBarEmpty::setFeelingFilter(bool isEnabled, Feeling feeling)
{
    if (_currentTab == nullptr)
        return;

    std::vector<std::shared_ptr<IFilter>> filters = _currentTab->getFilters();
    if (isEnabled) {
        filters.push_back(std::shared_ptr<IFilter>(new FeelingFilter(feeling)));
    } else {
        filters.erase(std::remove_if(filters.begin(), filters.end(),
                                     [=](const std::shared_ptr<IFilter>& f) {
                                         FeelingFilter* sf = dynamic_cast<FeelingFilter*>(f.get());
                                         return sf && sf->getFeeling() == feeling;
                                     }), filters.end());
    }
    _currentTab->setFilters(filters);
    saveAndPushChanges();
}

void SideBarEmpty::updateStarsCheckboxes()
{
    if (std::find_if(
            _currentTab->getFilters().begin(),
            _currentTab->getFilters().end(),
            [&](const std::shared_ptr<IFilter>& f) { return f->id() == STARS_FILTER && static_cast<StarsFilter*>(f.get())->getScore() == 1; }
            ) != _currentTab->getFilters().end())
        ui->onestar->setCheckState(Qt::Checked);
    else
        ui->onestar->setCheckState(Qt::Unchecked);

    if (std::find_if(
            _currentTab->getFilters().begin(),
            _currentTab->getFilters().end(),
            [&](const std::shared_ptr<IFilter>& f) { return f->id() == STARS_FILTER && static_cast<StarsFilter*>(f.get())->getScore() == 2; }
            ) != _currentTab->getFilters().end())
        ui->twoStars->setCheckState(Qt::Checked);
    else
        ui->twoStars->setCheckState(Qt::Unchecked);

    if (std::find_if(
            _currentTab->getFilters().begin(),
            _currentTab->getFilters().end(),
            [&](const std::shared_ptr<IFilter>& f) { return f->id() == STARS_FILTER && static_cast<StarsFilter*>(f.get())->getScore() == 3; }
            ) != _currentTab->getFilters().end())
        ui->threestars->setCheckState(Qt::Checked);
    else
        ui->threestars->setCheckState(Qt::Unchecked);

    if (std::find_if(
            _currentTab->getFilters().begin(),
            _currentTab->getFilters().end(),
            [&](const std::shared_ptr<IFilter>& f) { return f->id() == STARS_FILTER && static_cast<StarsFilter*>(f.get())->getScore() == 4; }
            ) != _currentTab->getFilters().end())
        ui->fourstars->setCheckState(Qt::Checked);
    else
        ui->fourstars->setCheckState(Qt::Unchecked);

    if (std::find_if(
            _currentTab->getFilters().begin(),
            _currentTab->getFilters().end(),
            [&](const std::shared_ptr<IFilter>& f) { return f->id() == STARS_FILTER && static_cast<StarsFilter*>(f.get())->getScore() == 5; }
            ) != _currentTab->getFilters().end())
        ui->fivestars->setCheckState(Qt::Checked);
    else
        ui->fivestars->setCheckState(Qt::Unchecked);
}

void SideBarEmpty::updateFeelingsCheckboxes()
{
    if (std::find_if(
            _currentTab->getFilters().begin(),
            _currentTab->getFilters().end(),
            [&](const std::shared_ptr<IFilter>& f) { return f->id() == FEELING_FILTER
                                                            && static_cast<FeelingFilter*>(f.get())->getFeeling() == HAPPY; }
            ) != _currentTab->getFilters().end())
        ui->heureux->setCheckState(Qt::Checked);
    else
        ui->heureux->setCheckState(Qt::Unchecked);

    if (std::find_if(
            _currentTab->getFilters().begin(),
            _currentTab->getFilters().end(),
            [&](const std::shared_ptr<IFilter>& f) { return f->id() == FEELING_FILTER
                                                            && static_cast<FeelingFilter*>(f.get())->getFeeling() == SAD; }
            ) != _currentTab->getFilters().end())
        ui->sad->setCheckState(Qt::Checked);
    else
        ui->sad->setCheckState(Qt::Unchecked);

    if (std::find_if(
            _currentTab->getFilters().begin(),
            _currentTab->getFilters().end(),
            [&](const std::shared_ptr<IFilter>& f) { return f->id() == FEELING_FILTER
                                                            && static_cast<FeelingFilter*>(f.get())->getFeeling() == INSPIRED; }
            ) != _currentTab->getFilters().end())
        ui->inspired->setCheckState(Qt::Checked);
    else
        ui->inspired->setCheckState(Qt::Unchecked);

    if (std::find_if(
            _currentTab->getFilters().begin(),
            _currentTab->getFilters().end(),
            [&](const std::shared_ptr<IFilter>& f) { return f->id() == FEELING_FILTER
                                                            && static_cast<FeelingFilter*>(f.get())->getFeeling() == CALM; }
            ) != _currentTab->getFilters().end())
        ui->calm->setCheckState(Qt::Checked);
    else
        ui->calm->setCheckState(Qt::Unchecked);

    if (std::find_if(
            _currentTab->getFilters().begin(),
            _currentTab->getFilters().end(),
            [&](const std::shared_ptr<IFilter>& f) { return f->id() == FEELING_FILTER
                                                            && static_cast<FeelingFilter*>(f.get())->getFeeling() == EXCITED; }
            ) != _currentTab->getFilters().end())
        ui->excite->setCheckState(Qt::Checked);
    else
        ui->excite->setCheckState(Qt::Unchecked);
}

