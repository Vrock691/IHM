    #include "mainwindow.h"
    #include "inspectorview.h"
    #include "serializationservice.h"
    #include "defaultfilter.cpp"
    #include "defaultorderer.cpp"
    #include "imagemodel.h"
    #include "galleryview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    _selected(nullptr)
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

        // Création de ImageStack
        _imageStack = new QStackedWidget(this);

        _galleryView = new GalleryView(this);
        _tabContainer = _galleryView->getTabContainer();
        QVBoxLayout* layout = new QVBoxLayout(ui->galleryViewContainer);
        layout->setContentsMargins(0,0,0,0);
        layout->setSpacing(0);
        layout->addWidget(_imageStack);

        _imageViewer = new ImageViewer(this);
        _imageViewer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        _imageViewer->enableOutsideClick();

        _imageStack->addWidget(_galleryView);
        _imageStack->addWidget(_imageViewer);

        _imageStack->setCurrentWidget(_galleryView);

        connect(_inspectorView, &InspectorView::onModelChanged, this, &MainWindow::onInspectorModelChanged);
        connect(_tabContainer, &TabContainer::tabChanged, this, &MainWindow::onTabChanged);
        connect(_galleryView, &GalleryView::imageClicked, this, &MainWindow::onImageClicked);
        connect(_imageViewer, &ImageViewer::clickedOutsideImage, this, [this](){
            _imageStack->setCurrentWidget(_galleryView);
        });
        connect(_imageViewer, &ImageViewer::requestForward, this, [this]() {

            if (_currentIndex < 0) return;

            if (_currentIndex < _galleryView->getCurrentImages().size() - 1) {
                _currentIndex++;

                setSelected(_galleryView->getCurrentImages()[_currentIndex]);

                _imageViewer->updateNavigation(
                    _currentIndex > 0,
                    _currentIndex < _galleryView->getCurrentImages().size() - 1
                    );
            }
        });

        connect(_imageViewer, &ImageViewer::requestBackward, this, [this]() {

                if (_currentIndex > 0) {
                    _currentIndex--;

                    setSelected(_galleryView->getCurrentImages()[_currentIndex]);
                }

                _imageViewer->updateNavigation(
                    _currentIndex > 0,
                    _currentIndex < _galleryView->getCurrentImages().size() - 1
                    );
            });
    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }

    void MainWindow::onImageClicked(ImageModel* imageModel)
    {
        if (_selected == imageModel)
            openViewer();
        else
            setSelected(imageModel);
    }

    void MainWindow::openViewer()
    {
        _imageStack->setCurrentWidget(_imageViewer);
    }

    void MainWindow::setSelected(ImageModel* imageModel)
    {
        _selected = imageModel;

        for (int i = 0; i < _galleryView->getCurrentImages().size(); ++i) {
            if (_galleryView->getCurrentImages()[i]->path() == _selected->path()) {
                _currentIndex = i;
                break;
            }
        }

        if (_selected) {
            _inspectorView->setSelected(_selected);
            _sidebarStack->setCurrentWidget(_inspectorView);

            _imageViewer->setSelected(_selected);

            _imageViewer->updateNavigation(
                _currentIndex > 0,
                _currentIndex < _galleryView->getCurrentImages().size() - 1
            );
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
        _galleryView->refreshModel();
    }

    void MainWindow::onSidebarEmptyModelChanged()
    {
        _galleryView->refreshModel();
    }

    void MainWindow::clearSelection()
    {
        _selected = nullptr;
        _sidebarStack->setCurrentWidget(_sideBarEmpty);
    }

    void MainWindow::onTabChanged(TabModel* model) {
        currentTab = model;
        clearSelection();
    }
