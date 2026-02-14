#ifndef TABBUTTONWIDGET_H
#define TABBUTTONWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class TabButtonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TabButtonWidget(const QString& name, QWidget* parent = nullptr);

    QString title() const;
    void setTitle(const QString& name);
    void setActive(bool active);

signals:
    void clicked();
    void closeRequested();
    void renameRequested();

private:
    QPushButton* _titleButton;
    QPushButton* _closeButton;

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

};

#endif
 // TABBUTTONWIDGET_H

