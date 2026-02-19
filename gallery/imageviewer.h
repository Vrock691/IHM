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

    void setImages(const std::vector<ImageModel>& images);
    void setSelected(const ImageModel* imageModel);
    void setImages(const std::vector<ImageModel>& images, int currentIndex = 0);


signals:
    void requestForward();
    void requestBackward();

private slots:
    void onNextClicked();
    void onPrevClicked();

private:
    Ui::ImageViewer *ui;
    ImageRenderer* _renderer = nullptr;
    std::vector<ImageModel> _images;
};

#endif // IMAGEVIEWER_H
