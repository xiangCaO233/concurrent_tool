//
// Created by 2333 xiang on 2024/9/3.
//

#ifndef CONCURRENT_TOOLKIT_DRAGGABLEWIDGET_H
#define CONCURRENT_TOOLKIT_DRAGGABLEWIDGET_H

#include "UndecoratedWidget.h"
#include "QMouseEvent"

class DraggableWidget : public UndecoratedWidget {
public:
    //缓存鼠标按下时位置
    QPoint tempPos;
    bool isMousePressing{false};

    DraggableWidget():UndecoratedWidget(){};

protected:
    //鼠标按下事件
    void mousePressEvent(QMouseEvent *event) override;

    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event) override;

    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event) override;

};


#endif //CONCURRENT_TOOLKIT_DRAGGABLEWIDGET_H
