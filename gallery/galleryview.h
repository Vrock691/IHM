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
    explicit GalleryView(QWidget *parent = nullptr);

    void refreshModel();

    TabContainer* getTabContainer();
    std::vector<ImageModel*> getCurrentImages();

signals:
    void onRequestSelect(ImageModel* imageModel);
    void imageClicked(ImageModel* imageModel);
    void indexationFinished();
    void widgetLoaded();

protected slots:
    void showIndexedPictures();
    void startIndexation();

private:
    Ui::GalleryVue *ui;
    TabContainer* _tabContainer;

    // Stockage des données
    std::vector<ImageModel*> _allImages;
    std::vector<ImageModel*> _currentImages;
    
    //organise les ImageCell dans le widget galleryGrid
    QGridLayout* _gridLayout;
    QVBoxLayout* _tabLayout;
    void populate();
    std::vector<ImageModel*> getImages();
    bool imageIndexed = false;
};

#endif // GALLERYVIEW_H
