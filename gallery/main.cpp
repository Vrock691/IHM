#include "galleryvue.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GalleryVue w;
    w.show();
    return a.exec();
}
