#include "mainwindow.h"
#include "inspectorview.h"
#include "imagemodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _selected = nullptr;

    _inspectorView = new InspectorView(this);
    ui->dockInspector->setWidget(_inspectorView);

    // Bloque le dock
    ui->dockInspector->setFeatures(QDockWidget::NoDockWidgetFeatures);

    //QObject::connect(_galleryView, &GalleryView::onRequestSelected);

    // Test
    ImageModel* testImage = new ImageModel(":/icons/image-icon.png");
    _inspectorView->setSelected(testImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// TODO: relier au slot "onRequestSelect" de GalleryView
void MainWindow::onGalleryRequestSelect(ImageModel imageModel)
{
    _selected = /*A supprimer -> */&/* <-*/imageModel;    // le paramètre sera déjà un pointeur après la refacto
    //_galleryView.setSelected(imageModel);
    _inspectorView->setSelected(/*A supprimer -> */&/* <-*/imageModel);   // idem
}
