#include "trackitem.h"
#include "ui_trackitem.h"

TrackItem::TrackItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TrackItem)
{
    ui->setupUi(this);
}

TrackItem::~TrackItem()
{
    delete ui;
}
