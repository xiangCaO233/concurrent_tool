//
// Created by 2333 xiang on 2024/9/4.
//

#ifndef CONCURRENT_TOOLKIT_CLOSEABLEWIDGET_H
#define CONCURRENT_TOOLKIT_CLOSEABLEWIDGET_H
#include "DraggableWidget.h"
#include "QMenu"

class CloseableWidget : public DraggableWidget{
public:
    CloseableWidget():DraggableWidget(){};

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
};


#endif //CONCURRENT_TOOLKIT_CLOSEABLEWIDGET_H
