#include "tabcontainer.h"
#include "tabbuttonwidget.h"
#include "tabmodel.h"
#include <QInputDialog>
#include <QVBoxLayout>
#include "serializationservice.h"
#include "defaultorderer.cpp"

TabContainer::TabContainer(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::TabContainer)
{
    ui->setupUi(this);

    // Déserialisation des onglets
    SerializationService service;
    _tabs = service.deserializeTabModels();
    if (_tabs.size() > 0) {
        for (int i = 0; i < (int) _tabs.size(); i++) {
            instanciateTab(_tabs[i], i);
        }
    }

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
    });

    // Suppression onglet
    connect(tabBtn, &TabButtonWidget::closeRequested, this, [=]() {
       if (ui->tabBarLayout->count() <= 1) return;

        tabBtn->deleteLater();
        _tabs.erase(_tabs.begin() + index);

        // TODO: Ajouter la suppression dans le dossier de l'application.

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
    std::unique_ptr<IOrderer> default_orderer = std::unique_ptr<IOrderer>(new DefaultOrderer());
    TabModel* newModel = new TabModel(_tabs.size()+1, name, {}, std::move(default_orderer));

    _tabs.push_back(newModel);
    instanciateTab(newModel, _tabs.size()+1);
}

TabContainer::~TabContainer()
{
    delete ui;
    for (int i = 0; i < (int) _tabs.size(); ++i) {
        delete _tabs[i];
    }
}
