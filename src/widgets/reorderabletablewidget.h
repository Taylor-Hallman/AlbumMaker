#ifndef REORDERABLETABLEWIDGET_H
#define REORDERABLETABLEWIDGET_H

#include <QTableWidget>
#include <QDropEvent>

class ReorderableTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    ReorderableTableWidget(QWidget* widget = nullptr);
protected:
    void dropEvent(QDropEvent* event) override;
signals:
    void rowReordered();
};

#endif // REORDERABLETABLEWIDGET_H
