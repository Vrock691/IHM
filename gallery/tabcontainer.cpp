#include "tabcontainer.h"
#include "tabbuttonwidget.h"
#include "tabmodel.h"
#include <QInputDialog>
#include <QVBoxLayout>
#include "serializationservice.h"
#include "defaultorderer.cpp"

TabContainer::TabContainer(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::TabContainer),
    _currentTab(nullptr)
{
    ui->setupUi(this);

    // Déserialisation des onglets
    SerializationService service;
    _tabs = service.deserializeTabModels();
    if (_tabs.size() > 0) {
        for (int i = 0; i < (int) _tabs.size(); i++) {
            instanciateTab(_tabs[i], i);
        }
        _currentTab = _tabs[0];
    } else {
        newTab("Accueil");
        if (!_tabs.empty()) _currentTab = _tabs[0];
    }

    emit tabChanged(_currentTab);

    // Bouton + pour ajouter un onglet
    connect(ui->addTabButton, &QPushButton::clicked, this, [=]() {
        newTab("Nouvel onglet");
    });

    // Style général
    setStyleSheet(R"(
        #tabItem {
            background-color: #2b2b2b;
            border-radius: 6px;
        }
        #tabTitle {
            color: white;
            background: transparent;
            border: none;
            padding: 4px 8px;
        }
        #tabTitle:hover {
            background-color: #3a3a3a;
        }
        #tabClose {
            color: white;
            background: transparent;
            border: none;
        }
        #tabClose:hover {
            color: #ff5555;
        }
        QPushButton#addTabButton {
            background-color: #2b2b2b;
            color: white;
            border-radius: 6px;
            padding: 4px 10px;
        }
        QPushButton#addTabButton:hover {
            background-color: #3a3a3a;
        }
    )");
}

void TabContainer::instanciateTab(TabModel* model, int index)
{
    TabButtonWidget* tabBtn = new TabButtonWidget(model->getName());
    ui->tabBarLayout->insertWidget(ui->tabBarLayout->count() - 1, tabBtn);

    // Connexion clic sur onglet
    connect(tabBtn, &TabButtonWidget::clicked, this, [=]() {
        // Désactive tous les onglets
        for (QObject* obj : ui->tabBarContainer->children()) {
            TabButtonWidget* t = qobject_cast<TabButtonWidget*>(obj);
            if (t) t->setActive(false);
        }

        tabBtn->setActive(true);
        emit tabChanged(model);
    });

    // Suppression onglet
    connect(tabBtn, &TabButtonWidget::closeRequested, this, [=]() {
        if (ui->tabBarLayout->count() <= 2) return;
        tabBtn->deleteLater();
        auto it = std::find(_tabs.begin(), _tabs.end(), model);
        if (it != _tabs.end()) {
            _tabs.erase(it);
            emit tabChanged(_tabs[0]);
        }

        QString configsPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QString configFilePath = QString("%1/configs/tabs/%2.json")
                                     .arg(configsPath)
                                     .arg(model->getIndex());
        QFile file(configFilePath);
        file.remove();

        delete model;
    });

    // Renommage onglet
    connect(tabBtn, &TabButtonWidget::renameRequested, this, [=]() {
        bool ok;
        QString newName = QInputDialog::getText(this, "Renommer l'onglet",
                                                "Nouveau nom :", QLineEdit::Normal,
                                                tabBtn->title(), &ok);
        if (ok && !newName.isEmpty()) {
            tabBtn->setTitle(newName);
            model->setName(newName);
            SerializationService service;
            service.serializeTabModel(*model);
        }
    });

    // Active automatiquement le nouvel onglet
    tabBtn->setActive(true);
}

void TabContainer::newTab(const QString name) {
    std::shared_ptr<IOrderer> default_orderer = std::shared_ptr<IOrderer>(new DefaultOrderer());
    TabModel* newModel = new TabModel(_tabs.size(), name, {}, default_orderer);

    SerializationService service;
    service.serializeTabModel(*newModel);
    instanciateTab(newModel, _tabs.size());
    _tabs.push_back(newModel);
}

bool TabContainer::filterImageModelByCurrentTabFilters(ImageModel* model) {
    const auto& filters = _currentTab->getFilters();
    for (const auto& filter : filters) {
        if (!filter->isAcceptable(model)) {
            return false;
        }
    }
    return true;
}

void TabContainer::setCurrentTab(TabModel* model) {
    _currentTab = model;
}

std::shared_ptr<IOrderer> TabContainer::getCurrentTabOrderer() {
    return _currentTab->getOrderer();
}

TabContainer::~TabContainer()
{
    delete ui;
    for (int i = 0; i < (int) _tabs.size(); ++i) {
        delete _tabs[i];
    }
}
