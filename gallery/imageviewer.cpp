#include "imageviewer.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>


ImageViewer::ImageViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ImageViewer)
{
    ui->setupUi(this);

    qDebug() << "ImageViewer créé";

    connect(ui->nextButton, &QPushButton::clicked,
            this, &ImageViewer::onNextClicked);

    connect(ui->prevButton, &QPushButton::clicked,
            this, &ImageViewer::onPrevClicked);
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

void ImageViewer::setSelected(const ImageModel* imageModel)
{
    qDebug() << "ImageViewer::setSelected appelé avec"
             << (imageModel ? QString::fromStdString(imageModel->path()) : "nullptr");

    if (!imageModel) return;

    if (_renderer != nullptr) {
        ui->imageContainerLayout->removeWidget(_renderer);
        delete _renderer;
        _renderer = nullptr;
    }
    _renderer = new ImageRenderer(*imageModel, this);
    _renderer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->imageContainerLayout->addWidget(_renderer);
}

void ImageViewer::onNextClicked()
{
    emit requestForward();
}

void ImageViewer::onPrevClicked()
{
    emit requestBackward();
}
