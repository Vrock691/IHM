#include "imagerenderer.h"
#include "imagemodel.h"
#include "ui_imagerenderer.h"

ImageRenderer::ImageRenderer(ImageModel* imageModel, bool expandToKeepRatio, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ImageRenderer)
    , _imageModel(imageModel)
    , _expandToKeepRatio(expandToKeepRatio)
{
    ui->setupUi(this);

    QImage image;
    image.load(QString::fromStdString(_imageModel->path()));

    _pixmap = QPixmap::fromImage(image);
    if (_expandToKeepRatio)
        _pixmap.scaled(_pixmap.size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    else
        _pixmap.scaled(_pixmap.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->_label->setPixmap(_pixmap);
    ui->_label->setMinimumSize(50, 50);
    ui->_label->setAlignment(Qt::AlignCenter);
}

ImageRenderer::~ImageRenderer()
{
    delete ui;
}

void ImageRenderer::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    QPixmap transformedPixmap;

    if (_expandToKeepRatio)
        transformedPixmap = _pixmap.scaled(ui->_label->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    else
        transformedPixmap = _pixmap.scaled(ui->_label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    transformedPixmap = transformedPixmap.copy(_imageModel->cropRect());
    ui->_label->setPixmap(transformedPixmap);
}
