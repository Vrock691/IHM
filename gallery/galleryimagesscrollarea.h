#ifndef GALLERYIMAGESSCROLLAREA_H
#define GALLERYIMAGESSCROLLAREA_H

#include "ui_galleryimagesscrollarea.h"

class GalleryImagesScrollArea : public QScrollArea, private Ui::GalleryImagesScrollArea
{
    Q_OBJECT

public:
    explicit GalleryImagesScrollArea(QWidget *parent = nullptr);
};

#endif // GALLERYIMAGESSCROLLAREA_H
