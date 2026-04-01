#include "filedropwidget.h"
#include "qevent.h"
#include <QMimeDatabase>
#include <QMimeType>

FileDropWidget::FileDropWidget(QWidget *parent)
    : QWidget{parent}
{
    setAcceptDrops(true);
}

void FileDropWidget::setLabel(QLabel* label)
{
    this->label = label;
}

void FileDropWidget::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void FileDropWidget::dropEvent(QDropEvent* event)
{
    const auto urls = event->mimeData()->urls();
    if (!urls.isEmpty()) {
        for (const QUrl& url : urls) {
            QString path = url.toLocalFile();
            QMimeDatabase db;
            QMimeType type = db.mimeTypeForFile(path);
            QString mime = type.name();

            if (mime.startsWith("image/"))
                emit imageDropped(path);
            else if (mime.startsWith("audio/"))
                emit audioDropped(path);
            else {
                emit unsupportedFileDropped();
            }
        }
    }
}
