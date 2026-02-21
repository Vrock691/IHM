#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include "imagemodel.h"
#include "imagerenderer.h"
#include "ui_imageviewer.h"
#include <QEvent>
#include <QMouseEvent>

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
    void setSelected(ImageModel* imageModel);
    void setImages(const std::vector<ImageModel>& images, int currentIndex = 0);
    void enableOutsideClick();
    void updateNavigation(bool hasPrevious, bool hasNext);


signals:
    void requestForward();
    void requestBackward();
    void clickedOutsideImage();

private slots:
    void onNextClicked();
    void onPrevClicked();

private:
    Ui::ImageViewer *ui;
    ImageRenderer* _renderer = nullptr;
    std::vector<ImageModel> _images;
    QPushButton* _closeButton;

protected :
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // IMAGEVIEWER_H
