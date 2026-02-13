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
    std::vector<std::unique_ptr<IFilter>> filters;
    filters.push_back(std::unique_ptr<IFilter>(new DefaultFilter()));
    TabModel tabmodel = TabModel(
                            0,
                            "Tab",
                            std::move(filters),
                            std::unique_ptr<IOrderer>(new DefaultOrderer())
        );
    service.serializeTabModel(tabmodel);

    std::vector<std::unique_ptr<IFilter>> filters2;
    filters.push_back(std::unique_ptr<IFilter>(new DefaultFilter()));
    TabModel tabmodel2 = TabModel(
        1,
        "Tab1",
        std::move(filters2),
        std::unique_ptr<IOrderer>(new DefaultOrderer())
        );
    service.serializeTabModel(tabmodel2);

    std::vector<TabModel> tabs = service.deserializeTabModels();
    qDebug() << "debug";
}

MainWindow::~MainWindow() {}
