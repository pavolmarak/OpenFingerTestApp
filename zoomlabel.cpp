#include "zoomlabel.h"
#include <QDebug>

ZoomLabel::ZoomLabel(QWidget *parent)
{

}

void ZoomLabel::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0){

        emit zoomImgSignal(1.1,this->objectName());
    }
    else{
        emit zoomImgSignal(0.9,this->objectName());
    }
}
