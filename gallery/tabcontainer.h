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
    IOrderer* getCurrentTabOrderer();
    void setCurrentTab(TabModel* model);

signals:
    void tabChanged(TabModel* model);

private:
    void newTab(const QString name);
    void instanciateTab(TabModel* model, int index);

    Ui::TabContainer *ui;
    std::vector<TabModel*> _tabs;
    TabModel* _currentTab;
};

#endif // TABMANAGER_H
