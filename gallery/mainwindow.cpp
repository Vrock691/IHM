#include "mainwindow.h"
#include "indexationservice.h"
#include "inspectorview.h"
#include "serializationservice.h"
#include "defaultfilter.cpp"
#include "defaultorderer.cpp"
#include "imagemodel.h"
#include "tabcontainer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    _selected(nullptr),
    _selectedImage(nullptr),
    _selectedCopy(":/images/default.png")
{
    ui->setupUi(this);

    _imageStack = new QStackedWidget(this);

    _imageViewer = new ImageViewer(this);

    _imageViewer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _imageStack->addWidget(_imageViewer);

    IndexationService indexService = IndexationService();
    QVector<ImageModel> fileImages = indexService.indexFiles(":/images");

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
    //std::vector<ImageModel> tempPourQueCaCompile = {};  // J'ai déplacé la récupération des images dans GalleryView
    //_tabContainer = new TabContainer(tempPourQueCaCompile, this);

    std::vector<ImageModel> imagesVector(fileImages.begin(), fileImages.end());
    _images = imagesVector;
    _tabContainer = new TabContainer(imagesVector, this);
    _tabContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _imageStack->addWidget(_tabContainer);

    connect(_tabContainer, &TabContainer::imageClicked, this, [this](ImageModel img) {
        for (int i = 0; i < _images.size(); ++i) {
            if (_images[i].path() == img.path()) {
                _currentIndex = i;
                break;
            }
        }

        _selectedCopy = img;
        setSelected(&_selectedCopy);
        _imageViewer->setSelected(&_selectedCopy);

        _imageViewer->updateNavigation(
            _currentIndex > 0,
            _currentIndex < _images.size() - 1
            );

        _imageStack->setCurrentWidget(_imageViewer);
    });

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->tabManagerContainer->layout());
    if (!layout) {
        layout=new QVBoxLayout(ui->tabManagerContainer);
        layout->setContentsMargins(0,0,0,0);
        layout->setSpacing(0);
    }

    layout->addWidget(_imageStack);
    _imageStack->setCurrentWidget(_tabContainer);

    _imageViewer->enableOutsideClick();
    connect(_imageViewer, &ImageViewer::clickedOutsideImage, this, [this](){
        _imageStack->setCurrentWidget(_tabContainer);
    });

    connect(_imageViewer, &ImageViewer::requestForward,
            this, []() {
                qDebug() << "Forward demandé";
            });

    connect(_imageViewer, &ImageViewer::requestBackward,
            this, []() {
                qDebug() << "Backward demandé";
            });

    connect(_imageViewer, &ImageViewer::requestForward,
            this, [this]() {

                if (_currentIndex < 0) return;

                if (_currentIndex < _images.size() - 1) {
                    _currentIndex++;

                    _selectedCopy = _images[_currentIndex];
                    setSelected(&_selectedCopy);
                    _imageViewer->setSelected(&_selectedCopy);

                    _imageViewer->updateNavigation(
                        _currentIndex > 0,
                        _currentIndex < _images.size() - 1
                        );
                }
            });

    connect(_imageViewer, &ImageViewer::requestBackward,
            this, [this]() {

                if (_currentIndex > 0) {
                    _currentIndex--;

                    _selectedCopy = _images[_currentIndex];
                    setSelected(&_selectedCopy);
                    _imageViewer->setSelected(&_selectedCopy);
                }

                _imageViewer->updateNavigation(
                    _currentIndex > 0,
                    _currentIndex < _images.size() - 1
                    );
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSelected(ImageModel* imageModel)
{
    _selected = imageModel;

    if (_selected) {
        _inspectorView->setSelected(_selected);
        _sidebarStack->setCurrentWidget(_inspectorView);

        if (_imageViewer)
            _imageViewer->setSelected(_selected);
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
