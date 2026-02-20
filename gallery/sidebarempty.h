#ifndef SIDEBAREMPTY_H
#define SIDEBAREMPTY_H

#include "tabmodel.h"
#include "ui_sidebarempty.h"

class SideBarEmpty : public QWidget
{
    Q_OBJECT

public:
    explicit SideBarEmpty(QWidget *parent = nullptr);
    ~SideBarEmpty();
    void setCurrentTab(TabModel* tab);
    void refreshModel();

signals:
    void onModelChanged();

private:
    Ui::SideBarEmpty *ui;
    TabModel* _currentTab = nullptr;

    void saveAndPushChanges();
    void setStarFilter(bool isEnabled, int starAmount);
    void setFeelingFilter(bool isEnabled, Feeling feeling);
    void updateStarsCheckboxes();
    void updateFeelingsCheckboxes();
};

#endif // SIDEBAREMPTY_H
