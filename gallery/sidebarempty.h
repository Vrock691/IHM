#ifndef SIDEBAREMPTY_H
#define SIDEBAREMPTY_H

#include "ui_sidebarempty.h"

class SideBarEmpty : public QWidget
{
    Q_OBJECT

public:
    explicit SideBarEmpty(QWidget *parent = nullptr);
    ~SideBarEmpty();

private:
    Ui::SideBarEmpty *ui;
};

#endif // SIDEBAREMPTY_H
