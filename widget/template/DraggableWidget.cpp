//
// Created by 2333 xiang on 2024/9/3.
//

#include "DraggableWidget.h"
void DraggableWidget::mousePressEvent(QMouseEvent *event) {
    //缓存鼠标位置
    tempPos = event->pos();
    isMousePressing = true;
}

void DraggableWidget::mouseMoveEvent(QMouseEvent *event) {
    if (isMousePressing)
        //计算拖动到的位置
        move(pos().x() + event->pos().x() - tempPos.x(), pos().y() + event->pos().y() - tempPos.y());
}

void DraggableWidget::mouseReleaseEvent(QMouseEvent *event) {
    isMousePressing = false;
}
