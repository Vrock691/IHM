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
    ui->iconEdit->setIconSize(QSize(18, 18));

    ui->iconHeart->setIcon(
        QIcon(":/icons/heart-icon.png")
        );
    ui->iconHeart->setIconSize(QSize(18, 18));

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
    ui->tabWidget->setIconSize(QSize(24, 24));

    ui->iconInfo->setPixmap(
        QPixmap(":/icons/info-icon.png")
            .scaled(18, 18, Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );

    ui->descriptionEdit->setPlaceholderText("Écrivez quelque chose...");

    refreshModel();

    // ------- Gestion des Tags ------- //

    QToolButton* plusBtn = new QToolButton(ui->tagsContainer);
    plusBtn->setText("+");
    plusBtn->setFixedSize(28, 28);
    plusBtn->setToolTip("Ajouter un mot-clé");
    plusBtn->setStyleSheet(R"(
        QToolButton {
            background-color: white;
            color: black;
            font-weight: bold;
            font-size: 18px;
            border-radius: 6px;
            border: 1px solid #CCCCCC;
        }
        QToolButton:hover {
            background-color: #F2F2F2;
        }
        QToolButton:pressed {
            background-color: #E0E0E0;
        }
        )");

    _tagInput = new QLineEdit(ui->tagsContainer);
    _tagInput->setPlaceholderText("Mot clé");
    _tagInput->hide();
    _addTagBtn->setStyleSheet(R"(
        QPushButton {
            background-color: white;
            color: black;
            font-weight: 600;
            padding: 6px 12px;
            border-radius: 6px;
            border: 1px solid #CCCCCC;
        }
        QPushButton:hover {
            background-color: #F2F2F2;
        }
        QPushButton:pressed {
            background-color: #E0E0E0;
        }
        )");

    _addTagBtn = new QPushButton("Ajouter", ui->tagsContainer);
    _addTagBtn->hide();

    // Supprimer l'ancien layout si besoin
    QLayout* oldLayout = ui->tagsContainer->layout();
    if (oldLayout) delete oldLayout;

    // Layout vertical principal
    QVBoxLayout* containerLayout = new QVBoxLayout(ui->tagsContainer);
    containerLayout->setContentsMargins(0,0,0,0);
    containerLayout->setSpacing(4);

    // Layout horizontal pour les tags
    _tagsLayout = new QHBoxLayout();
    _tagsLayout->setSpacing(4);

    // Ajouter en vertical : boutons puis tags
    containerLayout->addWidget(plusBtn);
    containerLayout->addWidget(_tagInput);
    containerLayout->addWidget(_addTagBtn);
    containerLayout->addLayout(_tagsLayout);
    containerLayout->addStretch();

    // ------- Connexions ------- //
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

    // ------- Titre (infos générales) ------- //

    ui->genInfosTitle->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->genInfosTitle->setSpacing(4);
    ui->genInfosTitle->setContentsMargins(0, 0, 0, 0);


    // ------- Grille des propriétés (infos générales) ------- //

    ui->propsGridLayout->setColumnStretch(0, 1);
    ui->propsGridLayout->setColumnStretch(1, 3);

    // ------- Gestion des étoiles ------- //

    QHBoxLayout* ratingLayout = new QHBoxLayout();
    ratingLayout->setContentsMargins(0, 0, 0, 0);
    ratingLayout->setSpacing(0);
    ratingLayout->setAlignment(Qt::AlignLeft);

    const int maxStars = 5;
    for (int i = 0; i < maxStars; ++i) {
        QToolButton* star = new QToolButton(ui->ratingContainer);
        star->setCheckable(false);
        star->setIcon(QIcon(":/icons/star-empty-icon.png"));
        star->setIconSize(QSize(20, 20));
        star->setStyleSheet(
            "QToolButton { border: none; background: transparent; }"
            );

        ratingLayout->addWidget(star);
        _starButtons.append(star);

        connect(star, &QToolButton::clicked, this, [=]() {
            setRating(i + 1);
        });
    }

    ui->ratingContainer->setLayout(ratingLayout);

    // ------- Gestion des couleurs dominantes ------- //

    QVBoxLayout* colorsTitleLayout = qobject_cast<QVBoxLayout*>(ui->colorsTitleContainer);
    colorsTitleLayout->setSpacing(0);
    colorsTitleLayout->setContentsMargins(0, 0, 0, 0);

    ui->colorsTitle1->setContentsMargins(0, 0, 0, 0);
    ui->colorsTitle2->setContentsMargins(0, 0, 0, 0);


}

InspectorView::~InspectorView()
{
    delete ui;
}

void InspectorView::setSelected(ImageModel* imageModel)
{
    _selected = imageModel;

    refreshModel();
}

void InspectorView::refreshModel()
{
    if (!_selected) {
        ui->labelFileName->setText("Aucune image sélectionnée");
        ui->labelPath->clear();
        ui->labelFormat->clear();
        ui->labelSize->clear();
        ui->labelDimensions->clear();
        return;
    }

    ui->labelFileName->setText(
        QString::fromStdString(_selected->fileName())
        );

    ui->labelPath->setText(
        QString::fromStdString(_selected->path())
        );

    ui->labelFormat->setText(
        QString::fromStdString(_selected->format())
        );

    ui->labelDimensions->setText(
        QString("%1 x %2")
            .arg(_selected->width())
            .arg(_selected->height())
        );

    double sizeKB = _selected->sizeBytes() / 1024.0;
    ui->labelSize->setText(
        QString::number(sizeKB, 'f', 2) + " Ko"
        );
}

void InspectorView::addTag(const QString &text)
{
    QWidget* tag = new QWidget(ui->tagsContainer);
    QHBoxLayout* tagLayout = new QHBoxLayout(tag);
    tagLayout->setContentsMargins(8,2,6,2);
    tagLayout->setSpacing(4);

    QLabel* label = new QLabel(text);
    QToolButton* removeBtn = new QToolButton();
    removeBtn->setText("✕");

    tagLayout->addWidget(label);
    tagLayout->addWidget(removeBtn);

    tag->setStyleSheet(R"(
        QWidget { background-color: #3A3A3A; border-radius: 10px; }
        QLabel { color: #E0E0E0; }
        QToolButton { border: none; background: transparent; color: #AAAAAA; }
        QToolButton:hover { color: #FF5C5C; }
    )");

    _tagsLayout->addWidget(tag);

    connect(removeBtn, &QToolButton::clicked, this, [=]() {
        tag->deleteLater();
    });
}

void InspectorView::setRating(int rating)
{
    _currentRating = rating;

    for (int i = 0; i < _starButtons.size(); ++i) {
        if (i < rating)
            _starButtons[i]->setIcon(QIcon(":/icons/star-filled-icon.png"));
        else
            _starButtons[i]->setIcon(QIcon(":/icons/star-empty-icon.png"));
    }

    if (_selected)
        _selected->setScore(rating);
}
