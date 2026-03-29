#include "imagedropwidget.h"
#include "qevent.h"

ImageDropWidget::ImageDropWidget(QWidget *parent)
    : QWidget{parent}
{
    setAcceptDrops(true);
}

void ImageDropWidget::setLabel(QLabel* label)
{
    this->label = label;
}

void ImageDropWidget::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void ImageDropWidget::dropEvent(QDropEvent* event)
{
    const auto urls = event->mimeData()->urls();
    if (!urls.isEmpty())
        emit imageDropped(urls.first().toLocalFile());
}
