#include "galleryview.h"
#include "imagecell.h"
#include "indexationservice.h"
#include <QGridLayout>
#include <QDebug>
#include "serializationservice.h"
#include <algorithm>

GalleryView::GalleryView(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::GalleryVue)
{
    ui->setupUi(this);

    // Setup Tab Container
    _tabContainer = new TabContainer(this);
    ui->tabLayout->addWidget(_tabContainer);
    _tabContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    // Setup Gallery Grid
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    ui->scrollArea->setWidgetResizable(true);

    QWidget* container = ui->scrollArea->widget();
    _gridLayout = new QGridLayout(container);

    _gridLayout->setContentsMargins(0,0,0,0);
    _gridLayout->setSpacing(10);

    _gridLayout->setRowStretch(0, 1);
    _gridLayout->setColumnStretch(0, 1);
    _gridLayout->setColumnStretch(1, 1);
    _gridLayout->setColumnStretch(2, 1);
    _gridLayout->setColumnStretch(3, 1);

    ui->scrollArea->setStyleSheet("background: transparent;");

    _allImages = getImages();
    refreshModel();
}

TabContainer* GalleryView::getTabContainer()
{
    return _tabContainer;
}

std::vector<ImageModel*> GalleryView::getCurrentImages()
{
    return _currentImages;
}

std::vector<ImageModel*> GalleryView::getImages()
{
    IndexationService indexService = IndexationService();
    qDebug() << "Début de l'indexation";

    QString picturesPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    qDebug() << "Chemin racine des images :" << picturesPath;

    QVector<ImageModel> qFileImages = indexService.indexFiles(":/images"); // à remplacer par picturesPath
    //QVector<ImageModel> qFileImages = indexService.indexFiles("/home");
    qDebug() << "Fin de l'indexation";

    std::vector<ImageModel> fileImages(qFileImages.begin(), qFileImages.end());

    SerializationService serialisationService = {};
    std::vector<ImageModel*> deserializedImages = serialisationService.deserializeImageModels();
    std::vector<ImageModel*> unionImages = {};

    foreach (ImageModel image, fileImages) {
        auto foundInDeserialized = std::find_if(
            deserializedImages.begin(),
            deserializedImages.end(),
            [=](ImageModel* i) { return i->path() == image.path(); }  // pointeur : i* et ->
            );

        bool isInDeserialized = foundInDeserialized != deserializedImages.end();
        if (isInDeserialized)
            unionImages.push_back(*foundInDeserialized);
        else
            unionImages.push_back(new ImageModel(image));  // on crée un pointeur, pas une copie valeur
    }

    return unionImages;
}

void GalleryView::refreshModel()
{
    // Supprime les anciennes cellules
    QLayoutItem* child;
    while ((child = _gridLayout->takeAt(0)) != nullptr) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }

    int columnCount = 4;

    std::sort(_allImages.begin(), _allImages.end(), [this](ImageModel* a, ImageModel* b) {
        return _tabContainer->getCurrentTabOrderer()->orderer(a, b);
    });
    _currentImages.clear();

    for (size_t i = 0; i < _allImages.size(); ++i) {
        bool accepted = _tabContainer->filterImageModelByCurrentTabFilters(_allImages[i]);
        if (accepted) {
            // Nécessaire pour que GalleryView puisse avoir accès aux images actuelles
            _currentImages.push_back(_allImages[i]);
        }
    }

    for (size_t i = 0; i < _currentImages.size(); ++i) {
        ImageCell* cell = new ImageCell(_currentImages[i]);
        cell->setMinimumSize(120, 120);
        cell->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        connect(cell, &ImageCell::clicked, this, [this](ImageModel* image) {
            emit imageClicked(image);
        });

        int row = i / columnCount;
        int col = i % columnCount;

        _gridLayout->addWidget(cell, row, col);
        _gridLayout->setRowStretch(row, 1);

    }
}
