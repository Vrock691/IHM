#ifndef IMAGECELL_H
#define IMAGECELL_H

#include <QWidget>
#include "imagemodel.h"
#include "imagerenderer.h"

namespace Ui {
class ImageCell;
}

class ImageCell : public QWidget
{
    Q_OBJECT

public:
    explicit ImageCell(ImageModel* imageModel, QWidget *parent = nullptr);
    ~ImageCell();

private:
    Ui::ImageCell *ui;
    ImageRenderer* _imageRenderer;

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void clicked(ImageModel* image);
};

#endif // IMAGECELL_H
