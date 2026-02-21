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

    bool filterImageModelByCurrentTabFilters(ImageModel* image);
    std::vector<ImageModel*> orderImageModelsByCurrentTabOrderer(std::vector<ImageModel*> images);

signals:
    void tabChanged(TabModel* model);

private:
    void newTab(const QString name);
    void instanciateTab(TabModel* model, int index);

    void setCurrentTabId(int id);
    int _currentTabId = -1;

    Ui::TabContainer *ui;
    std::vector<TabModel*> _tabs;
};

#endif // TABMANAGER_H
