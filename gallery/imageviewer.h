#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include "imagemodel.h"
#include "imagerenderer.h"
#include "ui_imageviewer.h"

namespace Ui {
class ImageViewer;
}

class ImageViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent = nullptr);
    ~ImageViewer();

    void setSelected(const ImageModel* imageModel);

signals:
    void requestForward();
    void requestBackward();

private slots:
    void onNextClicked();
    void onPrevClicked();

private:
    Ui::ImageViewer *ui;
    ImageRenderer* _renderer = nullptr;
};

#endif // IMAGEVIEWER_H
