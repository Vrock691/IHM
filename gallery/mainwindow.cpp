#include "mainwindow.h"
#include "inspectorview.h"
#include "serializationservice.h"
#include "defaultfilter.cpp"
#include "defaultorderer.cpp"
#include "imagemodel.h"
#include "tabcontainer.h"
#include "galleryview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _sidebarStack = new QStackedWidget(this);

    // Empty state
    _sideBarEmpty = new SideBarEmpty(this);
    _sidebarStack->addWidget(_sideBarEmpty); // index 0

    // Inspecteur
    _inspectorView = new InspectorView(this);
    _sidebarStack->addWidget(_inspectorView); // index 1

    // Affiche par défaut l'empty state
    _sidebarStack->setCurrentWidget(_sideBarEmpty);

    // Mets le stacked widget dans le dock
    ui->dockInspector->setWidget(_sidebarStack);
    ui->dockInspector->setFeatures(QDockWidget::NoDockWidgetFeatures);

    // ------- Tab Container ------- //
    std::vector<ImageModel> tempPourQueCaCompile = {};  // J'ai déplacé la récupération des images dans GalleryView
    _tabContainer = new TabContainer(tempPourQueCaCompile, this);

    connect(_tabContainer, &TabContainer::imageClicked, this, [this](ImageModel img) {
        setSelected(&img);  // TODO: Corriger, devrait prendre un pointeur
    });

    QVBoxLayout* layout = new QVBoxLayout(ui->tabManagerContainer);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(_tabContainer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSelected(ImageModel* imageModel)
{
    _selected = imageModel;

    if(_selected) {
        _inspectorView->setSelected(_selected);
        _sidebarStack->setCurrentWidget(_inspectorView);
    } else {
        _sidebarStack->setCurrentWidget(_sideBarEmpty);
    }
}

void MainWindow::onGalleryRequestSelect(ImageModel imageModel)
{
    setSelected(&imageModel);
}

void MainWindow::onInspectorModelChanged()
{
    //_gallery_view.refreshModel();
}

void MainWindow::onSidebarEmptyModelChanged()
{
    //_gallery_view.refreshModel();
}

void MainWindow::clearSelection()
{
    _selected = nullptr;
    _sidebarStack->setCurrentWidget(_sideBarEmpty);
}
