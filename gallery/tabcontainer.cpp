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
        setCurrentTabId(0);
    } else {
        newTab("Accueil");
        if (!_tabs.empty()) _currentTab = _tabs[0];
    }

    //emit tabChanged(_currentTab);   // Ne sert à rien, personne aucun connect possible avant le constructeur

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

void TabContainer::init()
{
    emit tabChanged(_currentTab);
}

void TabContainer::instanciateTab(TabModel* model, int index)
{
    TabButtonWidget* tabBtn = new TabButtonWidget(model->getName());
    ui->tabBarLayout->insertWidget(ui->tabBarLayout->count() - 1, tabBtn);

    // Connexion clic sur onglet
    connect(tabBtn, &TabButtonWidget::clicked, this, [=]() {
        int currentIndex = -1;
        for (int i = 0; i < _tabs.size(); ++i) {
            TabButtonWidget* t = qobject_cast<TabButtonWidget*>(ui->tabBarLayout->itemAt(i)->widget());
            if (t == tabBtn){
                currentIndex = i;
                break;
            }
        }
        if (currentIndex != -1) setCurrentTabId(currentIndex);
    });
/*
    connect(tabBtn, &TabButtonWidget::clicked, this, [=]() {
        // Désactive tous les onglets
        for (QObject* obj : ui->tabBarContainer->children()) {
            if (t) t->setActive(false);
        }

        tabBtn->setActive(true);
        emit tabChanged(model);
    });
*/
    connect(tabBtn, &TabButtonWidget::closeRequested, this, [=]() {
        int removedIndex = -1;
        for (int i = 0; i < (int)_tabs.size(); ++i) {
            if (_tabs[i] == model) {
                removedIndex = i;
                break;
            }
        }

        if (removedIndex == -1) return;

        tabBtn->deleteLater();
        _tabs.erase(_tabs.begin() + removedIndex);
        delete model;

        for (int i = removedIndex; i < (int)_tabs.size(); ++i) {
            _tabs[i]->setIndex(i);
        }

        if (_tabs.empty()) {
            _currentTabId = -1;
            emit tabChanged(nullptr);
            return;
        }

        if (_currentTabId == removedIndex) {
            int newIndex = removedIndex - 1;
            if (newIndex < 0) newIndex = 0;
            setCurrentTabId(newIndex);
        } else if (_currentTabId > removedIndex) {
            _currentTabId--;
        }
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
    //_tabs.push_back(newModel);

    _tabs.push_back(newModel);
    setCurrentTabId(_tabs.size() - 1);

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

void TabContainer::setCurrentTabId(int id) {
    _currentTabId = id;

    for (int i = 0; i < _tabs.size(); ++i) {
        TabButtonWidget* tabBtn = qobject_cast<TabButtonWidget*>(
            ui->tabBarLayout->itemAt(i)->widget()
            );
        if (!tabBtn) continue;

        tabBtn->setActive(i == id);
    }

    if (id >= 0 && id < _tabs.size())
        emit tabChanged(_tabs[id]);
}


