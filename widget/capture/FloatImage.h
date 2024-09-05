//
// Created by 2333 xiang on 2024/9/1.
//

#ifndef CONCURRENT_TOOLKIT_FLOATIMAGE_H
#define CONCURRENT_TOOLKIT_FLOATIMAGE_H

#include "../template/DraggableWidget.h"
#include "../../tool/CaptureTool.h"
#include "QMouseEvent"
#include "QMenu"
#include "QApplication"
#include "QClipboard"

class FloatImage : public DraggableWidget {
    //图片本体
    QImage srcImage;
    QImage displayImage;
    //缓存鼠标按下时位置
    QPoint tempPos;
public:
    //初始化悬浮图片窗口
    explicit FloatImage(QImage &imageSource);

    //限制显示大小
    explicit FloatImage(QSize size);

    //设置悬浮图片
    void setImage(QImage &image);

protected:
    //绘制事件
    void paintEvent(QPaintEvent *event) override;


    void contextMenuEvent(QContextMenuEvent *event) override;
};


#endif //CONCURRENT_TOOLKIT_FLOATIMAGE_H
