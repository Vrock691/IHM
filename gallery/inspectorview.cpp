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

    refreshUi();

    // ------- Gestion des Tags ------- //

    QToolButton* plusBtn = new QToolButton(ui->tagsContainer);
    plusBtn->setText("+");
    plusBtn->setFixedSize(30, 30);
    plusBtn->setToolTip("Ajouter un mot-clé");
    plusBtn->setStyleSheet(R"(
        QToolButton {
            background-color: white;
            color: black;
            font-size: 16px;
            border-radius: 15px;
            border: none;
            padding: 5px;
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

    _addTagBtn = new QPushButton("Ajouter", ui->tagsContainer);
    _addTagBtn->setFixedSize(70, 25);
    _addTagBtn->hide();
    _addTagBtn->setStyleSheet(R"(
        QPushButton {
            background-color: white;
            color: black;
            padding: 6px 12px;
            border-radius: 4px;
            border: none;
        }
        QPushButton:hover {
            background-color: #F2F2F2;
        }
        QPushButton:pressed {
            background-color: #E0E0E0;
        }
        )");

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

    connect(ui->descriptionEdit, &QTextEdit::textChanged, this, [=]() {
        QString text = ui->descriptionEdit->toPlainText();
        setDescriptionModel(text);
    });

    connect(ui->feelingComboBox, &QComboBox::currentIndexChanged, this, [=](int index) {
        setFeeling(index);
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

    // Création du layout vertical pour les couleurs
    QVBoxLayout* colorsLayout = new QVBoxLayout();
    colorsLayout->setContentsMargins(0,0,0,0);
    colorsLayout->setSpacing(4);

    // Couleurs codées en dur (il faut qu'on récupére les vraies couleurs et qu'on les stocke ici
    QStringList colors = { "#AABBCC", "#334455", "#FF9900" };

    for (const QString& color : colors) {
        // Widget ligne
        QWidget* rowWidget = new QWidget(ui->dominantColorsContainer);
        QHBoxLayout* rowLayout = new QHBoxLayout(rowWidget);
        rowLayout->setContentsMargins(0,0,0,0);
        rowLayout->setSpacing(4);

        QFrame* square = new QFrame(rowWidget);
        square->setFixedSize(24,24);
        square->setStyleSheet(QString("background-color: %1; border-radius:3px;").arg(color));

        QLabel* label = new QLabel(color, rowWidget);

        rowLayout->addWidget(square);
        rowLayout->addWidget(label);
        rowLayout->addStretch();

        colorsLayout->addWidget(rowWidget);
    }

    // Affecte le layout vertical au container
    ui->dominantColorsContainer->setLayout(colorsLayout);
}

InspectorView::~InspectorView()
{
    delete ui;
}

void InspectorView::setSelected(ImageModel* imageModel)
{
    _selected = imageModel;

    refreshUi();
}

void InspectorView::refreshUi()
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

    showRatingUi(_selected->score());

    showTagsUi(_selected->keyWords());

    showDescriptionUi(QString::fromStdString(_selected->description()));

    showFeelingUi(_selected->feeling());
}

void InspectorView::saveModel()
{
    qDebug() << "saved";

    qDebug() << "Name: " << _selected->fileName();
    qDebug() << "Score: " << _selected->score();
    qDebug() << "Keywords: ";
    foreach (auto tag, _selected->keyWords()) {
        qDebug() << "    - " << tag;
    }
}


void InspectorView::setRating(int rating)
{
    //_currentRating = rating;

    if (!_selected)
        return;

    _selected->setScore(rating);
    showRatingUi(rating);
    saveModel();
}

void InspectorView::addTag(const QString &text)
{
    if (!_selected)
        return;

    _selected->keyWords().push_back(text.toStdString());

    addTagUi(text);
    saveModel();
}

void InspectorView::removeTag(const QString &text)
{
    if (!_selected)
        return;

    auto& keywords = _selected->keyWords();
    keywords.erase(
        std::remove_if(
            keywords.begin(),
            keywords.end(),
            [&text](const std::string& s){ return s == text.toStdString(); }
        ),
        keywords.end()
    );
    
    saveModel();
}

void InspectorView::setDescription(const QString& text)
{
    setDescriptionModel(text);
    showDescriptionUi(text);
}

void InspectorView::setFeeling(int index)
{
    if (!_selected || index < 0)
        return;

    QVariant data = ui->feelingComboBox->itemData(index);
    Feeling feeling = static_cast<Feeling>(data.toInt());

    _selected->setFeeling(feeling);

    showFeelingUi(_selected->feeling());
    saveModel();
}

void InspectorView::setDescriptionModel(const QString& text)
{
    if (!_selected)
        return;

    _selected->setDescription(text.toStdString());
    saveModel();
}

void InspectorView::showRatingUi(int rating)
{
    for (int i = 0; i < _starButtons.size(); ++i) {
        if (i < rating)
            _starButtons[i]->setIcon(QIcon(":/icons/star-filled-icon.png"));
        else
            _starButtons[i]->setIcon(QIcon(":/icons/star-empty-icon.png"));
    }
}

void InspectorView::showTagsUi(std::vector<std::string> keyWords)
{
    QLayoutItem *wItem;
    while ((wItem = _tagsLayout->takeAt(0)) != 0)
    {
        if (wItem->widget())
            wItem->widget()->setParent(NULL);
        delete wItem;
    }

    // Ajouter les tags actuels
    foreach (auto tag, keyWords) {
        addTagUi(QString::fromStdString(tag));
    }
}

void InspectorView::addTagUi(const QString& text)
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
        QWidget { background-color: #FFFFFF; border-radius: 10px; }
        QLabel { color: #1E1E1E; }
        QToolButton { border: none; background: transparent; color: #1E1E1E; }
        QToolButton:hover { color: #FF5C5C; }
    )");

    _tagsLayout->addWidget(tag);

    connect(removeBtn, &QToolButton::clicked, this, [=]() {
        removeTag(text);
        tag->deleteLater();
    });
}

void InspectorView::showDescriptionUi(const QString& text)
{
    QSignalBlocker blocker(ui->descriptionEdit);
    ui->descriptionEdit->setPlainText(text);
}

void InspectorView::showFeelingUi(const Feeling feeling)
{
    QSignalBlocker blocker(ui->feelingComboBox);
    ui->feelingComboBox->clear();
    ui->feelingComboBox->setPlaceholderText("Sélectionner...");

    std::vector<Feeling> feelings = getFeelings();
    std::vector<QString> feelingNames = getFeelingNames();

    for (int i = 0; i < feelings.size(); i++) {
        ui->feelingComboBox->addItem(feelingNames[i], QVariant::fromValue((int)feelings[i]));
    }

    int index = -1;
    for (int i = 0; i < feelings.size(); i++) {
        if (feelings[i] == feeling) {
            index = i;
        }
    }

    ui->feelingComboBox->setCurrentIndex(index);

    if (feeling == Feeling::UNKNOWN_FEELING)
        ui->feelingComboBox->setCurrentIndex(-1);
}
