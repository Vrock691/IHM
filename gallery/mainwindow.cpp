#include "mainwindow.h"
#include "inspectorview.h"
#include "imagemodel.h"

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
    ImageModel* testImage = new ImageModel(":/icons/image-icon.png");
    inspector->setSelected(testImage);
}

MainWindow::~MainWindow() {}
