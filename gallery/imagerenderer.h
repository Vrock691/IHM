#ifndef IMAGERENDERER_H
#define IMAGERENDERER_H

#include "imagemodel.h"
#include <QWidget>

namespace Ui {
class ImageRenderer;
}

class ImageRenderer : public QWidget
{
    Q_OBJECT

public:
    explicit ImageRenderer(ImageModel* imageModel, QWidget *parent = nullptr);
    ~ImageRenderer();

    ImageModel* imageModel() { return _imageModel; }

private:
    Ui::ImageRenderer *ui;
    ImageModel* _imageModel;
    QPixmap _pixmap;

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // IMAGERENDERER_H
