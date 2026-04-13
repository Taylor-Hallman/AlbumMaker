#ifndef REORDERABLETABLEWIDGET_H
#define REORDERABLETABLEWIDGET_H

#include <QTableWidget>
#include <QDropEvent>

class ReorderableTableWidget : public QTableWidget
{
public:
    ReorderableTableWidget(QWidget* widget = nullptr);
protected:
    void dropEvent(QDropEvent* event) override;
};

#endif // REORDERABLETABLEWIDGET_H
