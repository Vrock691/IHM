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
    GalleryView* _galleryView;
    QStackedWidget* _sidebarStack;
    InspectorView* _inspectorView;
    SideBarEmpty* _sideBarEmpty;

    void setSelected(ImageModel* imageModel);
    void clearSelection();

private slots:
    void onGalleryRequestSelect(ImageModel imageModel);
    void onInspectorModelChanged();
    void onSidebarEmptyModelChanged();

};
#endif // MAINWINDOW_H
