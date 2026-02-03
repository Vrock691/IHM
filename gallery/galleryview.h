#ifndef GALLERYVIEW_H
#define GALLERYVIEW_H

#include "ui_galleryview.h"

class GalleryView : public QWidget, private Ui::GalleryVue
{
    Q_OBJECT

public:
    explicit GalleryView(QWidget *parent = nullptr);
};

#endif // GALLERYVIEW_H
