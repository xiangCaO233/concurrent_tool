//
// Created by 2333 xiang on 2024/8/31.
//  截图窗口
//

#ifndef CONCURRENT_TOOLKIT_CAPTUREWIDGET_H
#define CONCURRENT_TOOLKIT_CAPTUREWIDGET_H

#include "FloatImage.h"
#include <QLabel>
#include <QMouseEvent>
#include <QDragMoveEvent>
#include "../../tool/PublicReferences.h"
#include "../../tool/CaptureTool.h"


class CaptureWidget : public UndecoratedWidget {
    //截图路径
    QPainterPath capturePath;
    //缓存路径起始点
    QPoint tempPos;
    //是否在修改截图区域
    bool editCapture;
    //指针位置信息
    QLabel posInfo;
    //图片悬浮窗
    FloatImage floatImage;

public:
    explicit CaptureWidget();
    void display();
protected:
    //绘制事件
    void paintEvent(QPaintEvent *event) override;
    //鼠标按下事件
    void mousePressEvent(QMouseEvent *event) override;
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event) override;
    //鼠标双击事件
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event) override;


};


#endif //CONCURRENT_TOOLKIT_CAPTUREWIDGET_H
