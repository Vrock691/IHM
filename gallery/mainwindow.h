#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imagemodel.h"
#include "inspectorview.h"
#include "ui_mainwindow.h"
#include "tabcontainer.h"
#include "sidebarempty.h"
#include "imageviewer.h"

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

    TabContainer* _tabContainer = nullptr;
    SideBarEmpty* _sideBarEmpty;
    QStackedWidget* _sidebarStack;

    ImageViewer* _imageViewer = nullptr;

    const ImageModel* _selectedImage = nullptr;
    ImageModel _selectedCopy;
    QStackedWidget* _imageStack = nullptr; // ← stacked widget pour galerie + ImageViewer




private slots:
    void onGalleryRequestSelect(ImageModel imageModel);
    void onInspectorModelChanged();
    void onSidebarEmptyModelChanged();
    void setSelected(ImageModel* imageModel);
    void clearSelection();

};
#endif // MAINWINDOW_H
