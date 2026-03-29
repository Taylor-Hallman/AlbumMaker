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
    void mousePressEvent(QMouseEvent* event) override {
        event->ignore();
    }
    void mouseReleaseEvent(QMouseEvent* event) override {
        event->ignore();
    }
    void mouseDoubleClickEvent(QMouseEvent* event) override {
        event->ignore();
    }
    void keyPressEvent(QKeyEvent* event) override {
        event->ignore();
    }
};

#endif // NOUSERSELECTLISTWIDGET_H
