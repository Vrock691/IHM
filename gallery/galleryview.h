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

signals:
    void onRequestSelect(ImageModel imageModel);
    void imageClicked(ImageModel imageModel);  // NOUVEAU SIGNAL

private:
    void openTab(int tabId);

    // Stockage des données
    std::vector<ImageModel> _allImages;
    std::vector<TabModel> _tabs;

    QGridLayout* _gridLayout;
    void populate();

};

#endif // GALLERYVIEW_H
