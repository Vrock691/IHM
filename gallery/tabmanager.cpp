#include "tabmanager.h"
#include "galleryview.h"
#include "tabbuttonwidget.h"
#include <QInputDialog>
#include <QVBoxLayout>

TabManager::TabManager(std::vector<ImageModel> images, QWidget *parent)
    : QWidget(parent),
    ui(new Ui::TabManager),
    _initialImages(images)
{
    ui->setupUi(this);

    // Premier onglet "Accueil"
    addTab("Accueil");

    // Bouton + pour ajouter un onglet
    connect(ui->addTabButton, &QPushButton::clicked, this, [=]() {
        addTab("Nouvel onglet");
    });

    // Style général des onglets
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

void TabManager::addTab(const QString &name)
{
    TabButtonWidget* tabBtn = new TabButtonWidget(name);
    ui->tabBarLayout->insertWidget(ui->tabBarLayout->count() - 1, tabBtn);

    // Crée la GalleryView pour ce nouvel onglet avec parent = contentStack
    GalleryView* gallery = new GalleryView(_initialImages, {}, ui->contentStack);
    ui->contentStack->addWidget(gallery);

    // Connexion clic sur onglet
    connect(tabBtn, &TabButtonWidget::clicked, this, [=]() {
        ui->contentStack->setCurrentWidget(gallery);

        // Désactive tous les onglets
        for (QObject* obj : ui->tabBarContainer->children()) {
            TabButtonWidget* t = qobject_cast<TabButtonWidget*>(obj);
            if (t) t->setActive(false);
        }

        tabBtn->setActive(true);
    });

    // Suppression onglet
    connect(tabBtn, &TabButtonWidget::closeRequested, this, [=]() {
        if (ui->contentStack->count() <= 1) return;

        ui->contentStack->removeWidget(gallery);
        gallery->deleteLater();
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
    ui->contentStack->setCurrentWidget(gallery);
    tabBtn->setActive(true);
}

TabManager::~TabManager()
{
    delete ui;
}
