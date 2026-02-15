#include "imagerenderer.h"
#include "imagemodel.h"
#include "ui_imagerenderer.h"

ImageRenderer::ImageRenderer(ImageModel imageModel, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ImageRenderer)
    , _imageModel(imageModel)
{
    ui->setupUi(this);

    QImage image;
    image.load(QString::fromStdString(_imageModel.path()));

    _pixmap = QPixmap::fromImage(image);
    _pixmap.scaled(_pixmap.size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
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
    QPixmap transformedPixmap = _pixmap.scaled(ui->_label->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    transformedPixmap = transformedPixmap.copy(_imageModel.cropRect());
    ui->_label->setPixmap(transformedPixmap);
}
