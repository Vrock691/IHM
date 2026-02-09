#ifndef GALLERYVIEW_H
#define GALLERYVIEW_H

#include <QWidget>
#include <vector>
#include <QGridLayout>
#include "ui_galleryview.h"
#include "imagemodel.h"
#include "tabmodel.cpp"

class GalleryView : public QWidget, private Ui::GalleryVue
{
    Q_OBJECT

public:
    explicit GalleryView(std::vector<ImageModel> images, 
                         std::vector<TabModel> tabs, 
                         QWidget *parent = nullptr);

    void refreshModel();

private:
    void openTab(int tabId);

    // Stockage des données
    std::vector<ImageModel> _allImages;
    std::vector<TabModel> _tabs;
    
    //organise les ImageCell dans le widget galleryGrid
    QGridLayout* _gridLayout;
};

#endif // GALLERYVIEW_H
