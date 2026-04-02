#ifndef FILEDROPWIDGET_H
#define FILEDROPWIDGET_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>
#include <QLabel>

class FileDropWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileDropWidget(QWidget *parent = nullptr);

    void setLabel(QLabel* label);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;

    void dropEvent(QDropEvent* event) override;

private:
    QLabel* label;

signals:
    void imageDropped(const QString& path);
    void audioDropped(const QString& path);
    void unsupportedFileDropped();
};

#endif // FILEDROPWIDGET_H
