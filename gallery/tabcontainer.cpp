#include "tabcontainer.h"
#include "tabbuttonwidget.h"
#include "tabmodel.h"
#include <QInputDialog>
#include <QVBoxLayout>
#include "serializationservice.h"

TabContainer::TabContainer(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::TabContainer)
{
    ui->setupUi(this);

    SerializationService service;
    _tabs = service.deserializeTabModels();

    // Premier onglet "Accueil"
    addTab("Accueil");

    // Bouton + pour ajouter un onglet
    connect(ui->addTabButton, &QPushButton::clicked, this, [=]() {
        addTab("Nouvel onglet");
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

void TabContainer::addTab(const QString &name)
{
    TabButtonWidget* tabBtn = new TabButtonWidget(name);
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
    });

    // Renommage onglet
    connect(tabBtn, &TabButtonWidget::renameRequested, this, [=]() {
        bool ok;
        QString newName = QInputDialog::getText(this, "Renommer l'onglet",
                                                "Nouveau nom :", QLineEdit::Normal,
                                                tabBtn->title(), &ok);
        if (ok && !newName.isEmpty())
            tabBtn->setTitle(newName);
    });

    // Active automatiquement le nouvel onglet
    tabBtn->setActive(true);
}

TabContainer::~TabContainer()
{
    delete ui;
}
