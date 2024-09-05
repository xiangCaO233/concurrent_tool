//
// Created by 2333 xiang on 2024/9/2.
//

#ifndef CONCURRENT_TOOLKIT_MAGNIFYSELECTOR_H
#define CONCURRENT_TOOLKIT_MAGNIFYSELECTOR_H

#include "../../tool/PublicReferences.h"
#include "../../App.h"
#include "../template/UndecoratedWidget.h"
#include <QSvgRenderer>
#include "MagnifyRes.h"
#include "QKeyEvent"
#include "QMenu"

class MagnifySelector : public DraggableWidget {

    //更新线程
    QThread updateThread;
    //选择的放大路径
    QPainterPath magnifyPath;
    //放大结果
    MagnifyRes magnifyRes;
    //边框宽度
    int borderSize = 8;
    //拖动框
    QRect dragRect;
    //缓存拖动标识
    bool isin{};

public:

    explicit MagnifySelector(QRect rect);

    void showZoom();

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

    void moveEvent(QMoveEvent *event) override;

    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    void updateDragRec();

    void updateResRec();
};


#endif //CONCURRENT_TOOLKIT_MAGNIFYSELECTOR_H
