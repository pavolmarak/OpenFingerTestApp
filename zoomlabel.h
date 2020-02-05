#ifndef ZOOMLABEL_H
#define ZOOMLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QWheelEvent>

class ZoomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ZoomLabel(QWidget *parent = nullptr);
    void wheelEvent(QWheelEvent *event) override;
signals:
    void zoomImgSignal(double,QString);
};

#endif // ZOOMLABEL_H
