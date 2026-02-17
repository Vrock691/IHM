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

private:
    Ui::SideBarEmpty *ui;
    TabModel* _currentTab = nullptr;
};

#endif // SIDEBAREMPTY_H
