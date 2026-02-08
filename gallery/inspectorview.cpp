#include "inspectorview.h"

InspectorView::InspectorView(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::InspectorView)
{
    ui->setupUi(this);

    ui->iconImage->setPixmap(
        QPixmap(":/icons/image-icon.png")
            .scaled(45, 45, Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );

    ui->iconEdit->setIcon(
        QIcon(":/icons/edit-icon.png")
        );
    ui->iconEdit->setIconSize(QSize(24, 24));

    ui->iconHeart->setIcon(
        QIcon(":/icons/heart-icon.png")
        );
    ui->iconHeart->setIconSize(QSize(24, 24));

    ui->tabWidget->setTabText(0, "");
    ui->tabWidget->setTabText(1, "");

    // Onglet 0 : aperçu / infos
    ui->tabWidget->setTabIcon(
        0,
        QIcon(":/icons/eye-icon.png")
        );

    // Onglet 1 : métadonnées/redimensionnement
    ui->tabWidget->setTabIcon(
        1,
        QIcon(":/icons/redimension-icon.png")
        );

    // Taille des icônes dans la barre d’onglets
    ui->tabWidget->setIconSize(QSize(32, 32));

    ui->iconInfo->setPixmap(
        QPixmap(":/icons/info-icon.png")
            .scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );

}

InspectorView::~InspectorView()
{
    delete ui;
}

void InspectorView::setSelected(ImageModel* imageModel)
{
    _selected = imageModel;

    if (!_selected) {
        ui->labelFileName->setText("Aucune image sélectionnée");
        ui->labelPath->clear();
        ui->labelFormat->clear();
        ui->labelSize->clear();
        ui->labelDimensions->clear();
        return;
    }

    ui->labelFileName->setText(
        QString::fromStdString(_selected->fileName())
        );

    ui->labelPath->setText(
        QString::fromStdString(_selected->path())
        );

    ui->labelFormat->setText(
        QString::fromStdString(_selected->format())
        );

    ui->labelDimensions->setText(
        QString("%1 x %2")
            .arg(_selected->width())
            .arg(_selected->height())
        );

    double sizeKB = _selected->sizeBytes() / 1024.0;
    ui->labelSize->setText(
        QString::number(sizeKB, 'f', 2) + " Ko"
        );
}

