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

private:
    void newTab(const QString name);
    void instanciateTab(TabModel* model, int index);
    std::vector<ImageModel*> filterImageModelsByCurrentTabFilters(std::vector<ImageModel*> images);
    std::vector<ImageModel*> orderImageModelsByCurrentTabOrderer(std::vector<ImageModel*> images);

    Ui::TabContainer *ui;
    std::vector<TabModel*> _tabs;
};

#endif // TABMANAGER_H
