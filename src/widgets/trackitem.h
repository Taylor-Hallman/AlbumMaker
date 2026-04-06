#ifndef TRACKITEM_H
#define TRACKITEM_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class TrackItem;
}

class TrackItem : public QListWidgetItem
{
    Q_OBJECT

public:
    explicit TrackItem(QWidget *parent = nullptr);
    ~TrackItem();

private:
    Ui::TrackItem *ui;
};

#endif // TRACKITEM_H
