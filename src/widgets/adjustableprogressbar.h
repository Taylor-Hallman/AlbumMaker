#ifndef ADJUSTABLEPROGRESSBAR_H
#define ADJUSTABLEPROGRESSBAR_H

#include <QProgressBar>
#include <QMouseEvent>

class AdjustableProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    using QProgressBar::QProgressBar;

private:
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    int getValueFromMousePos(int xPos);

signals:
    void valueEdited(int value);
    void mouseDragged(int value);
};

#endif // ADJUSTABLEPROGRESSBAR_H
