#include "tabbuttonwidget.h"
#include <QMenu>
#include <QContextMenuEvent>

TabButtonWidget::TabButtonWidget(const QString& name, QWidget* parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(4, 2, 4, 2);

    setObjectName("tabItem");

    _titleButton = new QPushButton(name);
    _titleButton->setFlat(true);
    _titleButton->setObjectName("tabTitle");

    _closeButton = new QPushButton("✕");
    _closeButton->setFixedSize(16,16);
    _closeButton->setObjectName("tabClose");

    layout->addWidget(_titleButton);
    layout->addWidget(_closeButton);

    connect(_titleButton, &QPushButton::clicked, this, &TabButtonWidget::clicked);

    connect(_closeButton, &QPushButton::clicked, this, &TabButtonWidget::closeRequested);
}

QString TabButtonWidget::title() const
{
    return _titleButton->text();
}

void TabButtonWidget::setTitle(const QString& name)
{
    _titleButton->setText(name);
}

void TabButtonWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    QAction* renameAction = menu.addAction("Renommer");
    QAction* deleteAction = menu.addAction("Supprimer");

    QAction* selected = menu.exec(event->globalPos());

    if (selected == renameAction)
        emit renameRequested();

    if (selected == deleteAction)
        emit closeRequested();
}

void TabButtonWidget::setActive(bool active)
{
    if (active)
        setStyleSheet("background-color: #3a3a3a; border-radius:6px;");
    else
        setStyleSheet("");
}
