#ifndef IMAGECELL_H
#define IMAGECELL_H

#include <QWidget>
#include "imageStruct.cpp"

namespace Ui {
class ImageCell;
}

class ImageCell : public QWidget
{
    Q_OBJECT

public:
    explicit ImageCell(Image imageModel, QWidget *parent = nullptr);
    ~ImageCell();

private:
    Ui::ImageCell *ui;
    Image _imageModel;
    QPixmap _pixmap;



protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // IMAGECELL_H
