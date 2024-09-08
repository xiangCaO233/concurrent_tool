//
// Created by 2333 xiang on 2024/9/4.
//

#include "ScreenRuler.h"

ScreenRuler::ScreenRuler() : CloseableWidget() {
    resize(800, 120);
}

void ScreenRuler::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setPen({pubRef::pink, 2});
    p.setBrush(pubRef::dBack);
    p.drawRoundedRect(rect(),4,4);


    int cPosition = 10;
    while (cPosition < width()){
        int length;
        if (cPosition % 50==0){
            length = 12;
        }else{
            length = 8;
        }
        p.drawLine(cPosition,0,cPosition,length);
        cPosition+=10;
    }
}

void ScreenRuler::keyPressEvent(QKeyEvent *event) {
    QWidget::keyPressEvent(event);
}

void ScreenRuler::mousePressEvent(QMouseEvent *event) {
    DraggableWidget::mousePressEvent(event);
}

void ScreenRuler::mouseReleaseEvent(QMouseEvent *event) {
    DraggableWidget::mouseReleaseEvent(event);
}

void ScreenRuler::mouseMoveEvent(QMouseEvent *event) {
    DraggableWidget::mouseMoveEvent(event);
}
