#ifndef INSPECTORVIEW_H
#define INSPECTORVIEW_H

#include "ui_inspectorview.h"

class InspectorView : public QWidget, private Ui::InspectorView
{
    Q_OBJECT

public:
    explicit InspectorView(QWidget *parent = nullptr);
};

#endif // INSPECTORVIEW_H
