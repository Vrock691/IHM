#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "galleryview.h"
#include "imagemodel.h"
#include "inspectorview.h"
#include "qstackedwidget.h"
#include "ui_mainwindow.h"
#include "sidebarempty.h"

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
    TabContainer* _tabContainer;
    QStackedWidget* _sidebarStack;
    InspectorView* _inspectorView;
    SideBarEmpty* _sideBarEmpty;

    void setSelected(ImageModel* imageModel);
    void clearSelection();

private slots:
    void onGalleryRequestSelect(ImageModel imageModel);
    void onInspectorModelChanged();
    void onSidebarEmptyModelChanged();
    void onTabChanged(TabModel*);

};
#endif // MAINWINDOW_H
