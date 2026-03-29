#ifndef IMAGEDROPWIDGET_H
#define IMAGEDROPWIDGET_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>
#include <QLabel>

class ImageDropWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageDropWidget(QWidget *parent = nullptr);

    void setLabel(QLabel* label);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;

    void dropEvent(QDropEvent* event) override;

private:
    QLabel* label;

signals:
    void imageDropped(const QString& path);
};

#endif // IMAGEDROPWIDGET_H
