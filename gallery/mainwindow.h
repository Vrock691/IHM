#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imagemodel.h"
#include "inspectorview.h"
#include "ui_mainwindow.h"

#include <QMainWindow>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ImageModel* _selected;
    // GalleryView _galleryView;
    InspectorView* _inspectorView;

private slots:
    void onGalleryRequestSelect(ImageModel imageModel);

};
#endif // MAINWINDOW_H
