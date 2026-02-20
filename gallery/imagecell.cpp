#include "imagecell.h"
#include "ui_imagecell.h"
#include <QFile>
#include <QDir>
#include <QMouseEvent>

ImageCell::ImageCell(ImageModel* imageModel, QWidget *parent)
    : QWidget(parent), ui(new Ui::ImageCell)
{
    ui->setupUi(this);

    _imageRenderer = new ImageRenderer(imageModel);
    ui->verticalLayout->addWidget(_imageRenderer);
}

ImageCell::~ImageCell()
{
    delete ui;
}

void ImageCell::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    emit clicked(_imageRenderer->imageModel());
}
