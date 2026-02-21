#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "galleryview.h"
#include "imagemodel.h"
#include "inspectorview.h"
#include "qstackedwidget.h"
#include "ui_mainwindow.h"
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
    TabModel* currentTab;
    GalleryView* _galleryView;
    TabContainer* _tabContainer = nullptr;
    QStackedWidget* _sidebarStack;
    InspectorView* _inspectorView;
    SideBarEmpty* _sideBarEmpty;

    ImageViewer* _imageViewer = nullptr;

    QStackedWidget* _imageStack = nullptr;
    int _currentIndex = -1;

protected:
    void changeEvent(QEvent *event) override;

signals:
    void onWindowLaunched();

private slots:
    void onGalleryRequestSelect(ImageModel imageModel);
    void onInspectorModelChanged();
    void onSidebarEmptyModelChanged();
    void onTabChanged(TabModel*);
    void onImageClicked(ImageModel* imageModel);
    void setSelected(ImageModel* imageModel);
    void openViewer();
    void clearSelection();
};
#endif // MAINWINDOW_H
