#ifndef GALLERYVIEW_H
#define GALLERYVIEW_H

#include <QWidget>
#include <vector>
#include <QGridLayout>
#include "tabcontainer.h"
#include "ui_galleryview.h"
#include "imagemodel.h"

class GalleryView : public QWidget
{
    Q_OBJECT

public:
    explicit GalleryView(TabContainer* tabContainer, QWidget *parent = nullptr);

    void refreshModel();

    std::vector<ImageModel*> getImages();

signals:
    void onRequestSelect(ImageModel* imageModel);
    void imageClicked(ImageModel* imageModel);

private:
    Ui::GalleryVue *ui;
    TabContainer* _tabContainer;

    // Stockage des données
    std::vector<ImageModel*> _allImages;
    
    //organise les ImageCell dans le widget galleryGrid
    QGridLayout* _gridLayout;
    QVBoxLayout* _tabLayout;
    void populate();

};

#endif // GALLERYVIEW_H
