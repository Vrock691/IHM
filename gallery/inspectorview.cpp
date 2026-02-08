#include "inspectorview.h"

InspectorView::InspectorView(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    iconImage->setPixmap(
        QPixmap(":/icons/image-icon.png")
            .scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );

    iconEdit->setPixmap(
        QPixmap(":/icons/edit-icon.png")
            .scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );

    iconHeart->setPixmap(
        QPixmap(":/icons/heart-icon.png")
            .scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );
}
