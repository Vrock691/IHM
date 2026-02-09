#include "inspectorview.h"

InspectorView::InspectorView(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::InspectorView)
{
    ui->setupUi(this);

    ui->iconImage->setPixmap(
        QPixmap(":/icons/image-icon.png")
            .scaled(45, 45, Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );

    ui->iconEdit->setIcon(
        QIcon(":/icons/edit-icon.png")
        );
    ui->iconEdit->setIconSize(QSize(24, 24));

    ui->iconHeart->setIcon(
        QIcon(":/icons/heart-icon.png")
        );
    ui->iconHeart->setIconSize(QSize(24, 24));

    ui->tabWidget->setTabPosition(QTabWidget::West);
    ui->tabWidget->setTabText(0, "");
    ui->tabWidget->setTabText(1, "");

    // Onglet 0 : aperçu / infos
    ui->tabWidget->setTabIcon(
        0,
        QIcon(":/icons/eye-icon.png")
        );

    // Onglet 1 : métadonnées/redimensionnement
    ui->tabWidget->setTabIcon(
        1,
        QIcon(":/icons/redimension-icon.png")
        );

    // Taille des icônes dans la barre d’onglets
    ui->tabWidget->setIconSize(QSize(32, 32));

    ui->iconInfo->setPixmap(
        QPixmap(":/icons/info-icon.png")
            .scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );

    ui->descriptionEdit->setPlaceholderText("Écrivez quelque chose...");

    refreshModel();

    // ------- Gestion des Tags ------- //

    _tagsLayout = nullptr;

    // --- Layout Tags ---
    QToolButton* plusBtn = new QToolButton(ui->tagsContainer);
    plusBtn->setText("+");

    _tagInput = new QLineEdit(ui->tagsContainer);
    _tagInput->setPlaceholderText("Mot clé");
    _tagInput->hide();

    _addTagBtn = new QPushButton("Ajouter", ui->tagsContainer);
    _addTagBtn->hide();

    // Layout vertical principal
    QVBoxLayout* mainLayout = new QVBoxLayout(ui->tagsContainer);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(4);

    mainLayout->addWidget(plusBtn);
    mainLayout->addWidget(_tagInput);
    mainLayout->addWidget(_addTagBtn);

    // Layout horizontal pour les tags
    _tagsLayout = new QHBoxLayout();
    _tagsLayout->setSpacing(4);
    mainLayout->addLayout(_tagsLayout);

    // --- Connexions ---
    connect(plusBtn, &QToolButton::clicked, this, [=]() {
        _tagInput->show();
        _addTagBtn->show();
        _tagInput->setFocus();
    });

    connect(_addTagBtn, &QPushButton::clicked, this, [=]() {
        QString text = _tagInput->text().trimmed();
        if (text.isEmpty()) return;

        addTag(text);

        _tagInput->clear();
        _tagInput->hide();
        _addTagBtn->hide();
    });
}
