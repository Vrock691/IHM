#include "galleryview.h"
#include "imagecell.h"
#include <QGridLayout>
#include <QDebug>

GalleryView::GalleryView(std::vector<ImageModel> images, std::vector<TabModel> tabs, QWidget *parent)
    : QWidget(parent), _allImages(images), _tabs(tabs)
{
    setupUi(this);

    // S'assure que le widget prend tout l'espace
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    galleryGrid->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Si galleryGrid n'a pas de layout, on en crée un
    _gridLayout = qobject_cast<QGridLayout*>(galleryGrid->layout());
    if (!_gridLayout) {
        _gridLayout = new QGridLayout(galleryGrid);
        _gridLayout->setContentsMargins(0,0,0,0);
        _gridLayout->setSpacing(10);
        galleryGrid->setLayout(_gridLayout);
    } else {
        _gridLayout->setSpacing(10);
    }

    // Remplit les images
    openTab(0);
}

void GalleryView::openTab(int tabId)
{
    Q_UNUSED(tabId);

    qDebug() << "Images count =" << _allImages.size();

    // Supprime les anciennes cellules
    QLayoutItem* child;
    while ((child = _gridLayout->takeAt(0)) != nullptr) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }

    int columnCount = 4;

    for (size_t i = 0; i < _allImages.size(); ++i) {
        ImageCell* cell = new ImageCell(_allImages[i]); // PAS galleryGrid comme parent
        cell->setMinimumSize(120,120);

        int row = i / columnCount;
        int col = i % columnCount;

        _gridLayout->addWidget(cell, row, col);
    }
}
