#include "reorderabletablewidget.h"

ReorderableTableWidget::ReorderableTableWidget(QWidget* widget) {
    Q_UNUSED(widget);
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    setDefaultDropAction(Qt::MoveAction);
    setSelectionBehavior(QAbstractItemView::SelectRows);
}

void ReorderableTableWidget::dropEvent(QDropEvent* event)
{
    int sourceRow = currentRow();
    int targetRow = rowAt(event->position().toPoint().y());

    if (targetRow == -1)
        targetRow = rowCount() - 1;

    if (sourceRow != targetRow) {
        if (sourceRow < targetRow)
            targetRow++;
        insertRow(targetRow);
        int offset = sourceRow > targetRow ? 1 : 0;

        for (int col = 0; col < columnCount(); col++)
            setItem(targetRow, col, takeItem(sourceRow + offset, col));

        removeRow(sourceRow + offset);
    }
}
