#include "mainwindow.h"
#include "indexationservice.h"
#include "inspectorview.h"
#include "imagemodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    IndexationService indexService = IndexationService();
    QVector<ImageModel> fileImages = indexService.indexFiles("/");

    // deserializedImages = SerialisationService::deserializeImageModels()

    // TODO: Union des deux (on peut faire une méthode privée à part)


    // TODO: Affichage de GalleryView
    //QObject::connect(_galleryView, &GalleryView::onRequestSelected);

    _inspectorView = new InspectorView(this);
    ui->dockInspector->setWidget(_inspectorView);
    ui->dockInspector->setFeatures(QDockWidget::NoDockWidgetFeatures);  // Bloque le dock

    setSelected(nullptr);

    // Test
    //ImageModel* testImage = new ImageModel(":/icons/image-icon.png");
    //_inspectorView->setSelected(testImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSelected(ImageModel* imageModel)
{
    _selected = imageModel;
    //_galleryView.setSelected(imageModel);
    _inspectorView->setSelected(imageModel);
}

// TODO: relier au slot "onRequestSelect" de GalleryView
void MainWindow::onGalleryRequestSelect(ImageModel imageModel)
{
    setSelected(/*A supprimer -> */&/* <-*/imageModel); // le paramètre sera déjà un pointeur après la refacto
}
