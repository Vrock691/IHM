#ifndef TABMANAGER_H
#define TABMANAGER_H

#include "ui_tabcontainer.h"
#include "galleryview.h"
#include <QWidget>

class TabContainer : public QWidget, Ui::TabContainer
{
    Q_OBJECT

public:
    explicit TabContainer(std::vector<ImageModel> images, QWidget *parent = nullptr);
    ~TabContainer();

    void addTab(const QString &name);
    GalleryView* currentGallery();

signals:
    void imageClicked(ImageModel imageModel);

private:
    Ui::TabContainer *ui;
    std::vector<ImageModel> _initialImages;
};

#endif // TABMANAGER_H
