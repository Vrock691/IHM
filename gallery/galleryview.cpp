#include "galleryview.h"
#include "imagecell.h"
#include "indexationservice.h"
#include <QGridLayout>
#include <QDebug>
#include "serializationservice.h"
#include "tabcontainer.h"

GalleryView::GalleryView(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::GalleryVue)
{
    ui->setupUi(this);

    // Setup Tab Container
    _tabContainer = new TabContainer(this);
    ui->tabLayout = _tabContainer;

    // Setup Gallery Grid
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->galleryGrid->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    _gridLayout = qobject_cast<QGridLayout*>(ui->galleryGrid->layout());
    if (!_gridLayout) {
        _gridLayout = new QGridLayout(ui->galleryGrid);
        _gridLayout->setContentsMargins(0,0,0,0);
        _gridLayout->setSpacing(10);
        ui->galleryGrid->setLayout(_gridLayout);
    } else {
        _gridLayout->setSpacing(10);
    }

    _gridLayout->setRowStretch(0, 1);
    _gridLayout->setColumnStretch(0, 1);
    _gridLayout->setColumnStretch(1, 1);
    _gridLayout->setColumnStretch(2, 1);
    _gridLayout->setColumnStretch(3, 1);

    _allImages = getImages();
    openTab(0);
}

std::vector<ImageModel> GalleryView::getImages()
{
    IndexationService indexService = IndexationService();
    QVector<ImageModel> qFileImages = indexService.indexFiles(":/images");
    // Pas idéal de le faire comme ça, il faudrait passer indexFiles() à un std::vector
    std::vector<ImageModel> fileImages(qFileImages.begin(), qFileImages.end());

    SerializationService serialisationService = {};
    std::vector<ImageModel> deserializedImages = serialisationService.deserializeImageModels();

    std::vector<ImageModel> unionImages(deserializedImages.begin(), deserializedImages.end());

    foreach (auto image, fileImages) {
        auto foundInDeserialized = find_if(
            deserializedImages.begin(),
            deserializedImages.end(),
            [=] (const ImageModel& i) { return i.path() == image.path(); }
            );

        bool isInDeserialized = foundInDeserialized != deserializedImages.end();
        if (isInDeserialized)
            continue;

        unionImages.push_back(image);
    }

    return unionImages;
}

void GalleryView::openTab(int tabId)
{
    Q_UNUSED(tabId);

    // Supprime les anciennes cellules
    QLayoutItem* child;
    while ((child = _gridLayout->takeAt(0)) != nullptr) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }

    int columnCount = 4;

    for (size_t i = 0; i < _allImages.size(); ++i) {

        // Check if imageModel is accepted by the tab here

        ImageCell* cell = new ImageCell(_allImages[i]);
        cell->setMinimumSize(120, 120);
        cell->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        connect(cell, &ImageCell::clicked, this, [this](ImageModel image) {
            emit imageClicked(image);
        });

        int row = i / columnCount;
        int col = i % columnCount;

        _gridLayout->addWidget(cell, row, col);

        _gridLayout->setRowStretch(row, 1);
    }
}
