#ifndef TABMANAGER_H
#define TABMANAGER_H

#include "tabmodel.h"
#include "ui_tabcontainer.h"
#include <QWidget>

class TabContainer : public QWidget, Ui::TabContainer
{
    Q_OBJECT

public:
    explicit TabContainer(QWidget *parent = nullptr);
    ~TabContainer();

    void addTab(const QString &name);

private:
    Ui::TabContainer *ui;
    std::vector<TabModel> _tabs;
};

#endif // TABMANAGER_H
