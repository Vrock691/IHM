#include "sidebarempty.h"

SideBarEmpty::SideBarEmpty(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::SideBarEmpty)
{
    ui->setupUi(this);

    ui->label->setAlignment(Qt::AlignCenter);

    ui->label->setStyleSheet(R"(
        QLabel {
            font-size: 20px;
            font-weight: 600;
            color: #555555;
        }
    )");
}

SideBarEmpty::~SideBarEmpty()
{
    delete ui;
}

void SideBarEmpty::setCurrentTab(TabModel* tab)
{
    _currentTab = tab;
}

void SideBarEmpty::refreshModel()
{
    // TODO: à implémenter
}
