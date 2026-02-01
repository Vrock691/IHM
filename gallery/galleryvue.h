#ifndef GALLERYVUE_H
#define GALLERYVUE_H

#include "ui_galleryvue.h"

class GalleryVue : public QWidget, private Ui::GalleryVue
{
    Q_OBJECT

public:
    explicit GalleryVue(QWidget *parent = nullptr);
};

#endif // GALLERYVUE_H
