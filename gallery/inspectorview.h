#ifndef INSPECTORVIEW_H
#define INSPECTORVIEW_H

#include "ui_inspectorview.h"
#include "imagemodel.h"

class InspectorView : public QWidget, private Ui::InspectorView
{
    Q_OBJECT

public:
    explicit InspectorView(QWidget *parent = nullptr);
    ~InspectorView();

    void setSelected(ImageModel* imageModel);
    void refreshModel();

private:
    Ui::InspectorView *ui;
    ImageModel* _selected = nullptr;
};

#endif // INSPECTORVIEW_H
