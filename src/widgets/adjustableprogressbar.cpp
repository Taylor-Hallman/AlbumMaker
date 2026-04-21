#include "adjustableprogressbar.h"

void AdjustableProgressBar::mouseReleaseEvent(QMouseEvent* event)
{
    int newVal = getValueFromMousePos(event->pos().x());
    this->setValue(newVal);
    emit valueEdited(newVal);
}

void AdjustableProgressBar::mouseMoveEvent(QMouseEvent* event)
{
    int newVal = getValueFromMousePos(event->pos().x());
    this->setValue(newVal);
    emit mouseDragged(newVal);
}

int AdjustableProgressBar::getValueFromMousePos(int xPos)
{
    xPos = std::clamp(xPos, 0, this->width());
    return xPos * 100 / this->width();
}
