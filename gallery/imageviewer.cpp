#include "imageviewer.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>


ImageViewer::ImageViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ImageViewer)
{
    ui->setupUi(this);

    _closeButton = new QPushButton("✕", this); // petite croix
    _closeButton->setFixedSize(30, 30);
    _closeButton->move(width() - 40, 10); // coin supérieur droit
    _closeButton->setStyleSheet(R"(
    QPushButton {
        background-color: rgba(0,0,0,0.5);
        color: white;
        border: none;
        font-size: 16px;
        border-radius: 15px;
    }
    QPushButton:hover {
        background-color: rgba(255,0,0,0.8);
    }
)");
    _closeButton->raise();
    connect(_closeButton, &QPushButton::clicked, this, &ImageViewer::clickedOutsideImage);


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

void ImageViewer::setSelected(ImageModel* imageModel)
{
    qDebug() << "ImageViewer::setSelected appelé avec"
             << (imageModel ? QString::fromStdString(imageModel->path()) : "nullptr");

    if (!imageModel) return;

    if (_renderer != nullptr) {
        ui->imageContainerLayout->removeWidget(_renderer);
        delete _renderer;
        _renderer = nullptr;
    }
    _renderer = new ImageRenderer(imageModel, false, this);
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

bool ImageViewer::eventFilter(QObject* obj, QEvent* event) {
    if (obj == this && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (_renderer && !_renderer->geometry().contains(mouseEvent->pos())) {
            emit clickedOutsideImage();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void ImageViewer::enableOutsideClick() {
    this->installEventFilter(this);
}

void ImageViewer::updateNavigation(bool hasPrevious, bool hasNext)
{
    ui->prevButton->setEnabled(hasPrevious);
    ui->nextButton->setEnabled(hasNext);

}

