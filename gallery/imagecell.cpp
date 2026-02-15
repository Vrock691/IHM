#include "imagecell.h"
#include "ui_imagecell.h"
#include <QFile>
#include <QDir>
#include <QMouseEvent>

ImageCell::ImageCell(ImageModel imageModel, QWidget *parent)
    : QWidget(parent), ui(new Ui::ImageCell), _imageModel(imageModel)
{
    ui->setupUi(this);

    QImage image;
    // qDebug() << "Exists?" << QFile::exists(QString::fromStdString(_imageModel.path));
    // qDebug() << "CWD:" << QDir::currentPath();
    image.load(QString::fromStdString(_imageModel.path()));

    _pixmap = QPixmap::fromImage(image);
    _pixmap.scaled(_pixmap.size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    ui->_label->setPixmap(_pixmap);
    ui->_label->setMinimumSize(50, 50);
}

ImageCell::~ImageCell()
{
    delete ui;
}

void ImageCell::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    // qDebug() << "works";
    ui->_label->setPixmap(_pixmap.scaled(ui->_label->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
}

void ImageCell::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    emit clicked(_imageModel);
}
