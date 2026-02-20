#ifndef INSPECTORVIEW_H
#define INSPECTORVIEW_H

#include "tabmodel.h"
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
    void refreshUi();

signals:
    void onModelChanged();

protected slots:
    void saveModel();
    void setRating(int rating);
    void addTag(const QString& text);
    void removeTag(const QString& text);
    void setDescription(const QString& text);
    void setFeeling(int index);

private:
    Ui::InspectorView *ui;
    ImageModel* _selected = nullptr;
    QHBoxLayout* _tagsLayout;
    QLineEdit* _tagInput;
    QPushButton* _addTagBtn;
    QList<QToolButton*> _starButtons;
    //int _currentRating = 0;

    void setDescriptionModel(const QString& text);

    void showRatingUi(int rating);
    void showTagsUi(std::vector<std::string> keyWords);
    void addTagUi(const QString& text);
    void showDescriptionUi(const QString& text);
    void showFeelingUi(const Feeling feeling);
};

#endif // INSPECTORVIEW_H
