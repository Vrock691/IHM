#ifndef INSPECTORVIEW_H
#define INSPECTORVIEW_H

#include "ui_inspectorview.h"
#include "imagemodel.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QToolButton>
#include <QPushButton>
#include <QLabel>
#include <QList>

class InspectorView : public QWidget, private Ui::InspectorView
{
    Q_OBJECT

public:
    explicit InspectorView(QWidget *parent = nullptr);
    ~InspectorView();

    void setSelected(ImageModel* imageModel);
    void refreshModel();
    void addTag(const QString& text);

private:
    Ui::InspectorView *ui;
    ImageModel* _selected = nullptr;
    QHBoxLayout* _tagsLayout;
    QLineEdit* _tagInput;
    QPushButton* _addTagBtn;
    QList<QToolButton*> _starButtons;
    int _currentRating = 0;
    void setRating(int rating);
};

#endif // INSPECTORVIEW_H
