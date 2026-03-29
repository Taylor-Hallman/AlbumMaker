#ifndef NOUSERSELECTLISTWIDGET_H
#define NOUSERSELECTLISTWIDGET_H

#include <QListWidget>
#include <QMouseEvent>
#include <QKeyEvent>

class NoUserSelectListWidget : public QListWidget
{
public:
    using QListWidget::QListWidget;
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // NOUSERSELECTLISTWIDGET_H
