#include "mainwindow.h"
#include "inspectorview.h"
#include "serializationservice.h"
#include "defaultfilter.cpp"
#include "defaultorderer.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InspectorView* inspector = new InspectorView(this);

    ui->dockInspector->setWidget(inspector);

    // Bloque le dock
    ui->dockInspector->setFeatures(QDockWidget::NoDockWidgetFeatures);

    // Fixe la taille
    // ui->dockInspector->setMinimumWidth(250);
    // ui->dockInspector->setMaximumWidth(250);
    // ui->dockInspector->setMinimumHeight(400);
    // ui->dockInspector->setMaximumHeight(400);

    // Test
    //ImageModel* testImage = new ImageModel(":/icons/image-icon.png");
    //inspector->setSelected(testImage);

    SerializationService service;
    std::vector<std::string> keywords;
    keywords.push_back("Key1");
    keywords.push_back("Key2");
    ImageModel imageModel = ImageModel(
        "path2",
        200,
        200,
        "png",
        "name",
        500,
        "28/25/20",
        "29/05/02",
        Color::WHITE,
        "desc",
        keywords,
        0,
        Feeling::HAPPY
        );
    service.serializeImageModel(imageModel);
    qDebug() << "qDebug";
    std::vector<ImageModel> images = service.deserializeImageModels();
    qDebug() << "qDebug";
}

MainWindow::~MainWindow() {}
