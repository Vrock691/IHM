#ifndef TABMANAGER_H
#define TABMANAGER_H

#include "ui_tabmanager.h"
#include "galleryview.h"
#include <QWidget>

class TabManager : public QWidget, Ui::TabManager
{
    Q_OBJECT

public:
    explicit TabManager(std::vector<ImageModel> images, QWidget *parent = nullptr);
    ~TabManager();

    void addTab(const QString &name);
    GalleryView* currentGallery();

signals:
    void imageClicked(ImageModel imageModel);

private:
    Ui::TabManager *ui;
    std::vector<ImageModel> _initialImages;
};

#endif // TABMANAGER_H
