#include "galleryview.h"
#include "imagecell.h"

GalleryView::GalleryView(std::vector<ImageModel> images, std::vector<TabModel>& tabs, QWidget *parent)
    : QWidget(parent), _allImages(images), _tabs(tabs)
{
    setupUi(this);

    //grille d'images
    _gridLayout = new QGridLayout(galleryGrid);
    galleryGrid->setLayout(_gridLayout);

    //on ouvre le premier onglet par défaut s'il existe
    if (!_tabs.empty()) {
        openTab(0);
    }
}


//on affiche les images sans ordre
void GalleryView::openTab(int tabId)
{
    QLayoutItem *child;
    while ((child = _gridLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            delete child->widget();
        }
        delete child;
    }

    int columnCount = 4;
    
    for (size_t i = 0; i < _allImages.size(); ++i) {
        ImageCell* cell = new ImageCell(_allImages[i], this);
        
        //position dans la grille
        int row = i / columnCount;
        int col = i % columnCount;
        
        _gridLayout->addWidget(cell, row, col);
    }
}
