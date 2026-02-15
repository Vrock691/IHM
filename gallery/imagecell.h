#ifndef IMAGECELL_H
#define IMAGECELL_H

#include <QWidget>
#include "imagemodel.h"

namespace Ui {
class ImageCell;
}

class ImageCell : public QWidget
{
    Q_OBJECT

public:
    explicit ImageCell(ImageModel imageModel, QWidget *parent = nullptr);
    ~ImageCell();

private:
    Ui::ImageCell *ui;
    ImageModel _imageModel;
    QPixmap _pixmap;

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void clicked(ImageModel image);
};

#endif // IMAGECELL_H
