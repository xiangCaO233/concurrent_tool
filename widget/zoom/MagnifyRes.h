//
// Created by 2333 xiang on 2024/9/2.
//

#ifndef CONCURRENT_TOOLKIT_MAGNIFYRES_H
#define CONCURRENT_TOOLKIT_MAGNIFYRES_H


#include <QThread>
#include <QTimer>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QRectF>
#include <QImage>
#include "ZoomUpdater.h"
#include "RateTip.h"
#include "../template/DraggableWidget.h"
#include "../../tool/CaptureTool.h"


class MagnifyRes : public DraggableWidget {
Q_OBJECT

    //区域更新器
    ZoomUpdater *updater;
    //最终绘制的图像
    QImage image;
    //记录鼠标当前位置
    QPoint currentPos{};
    //提示框计时器
    QTimer *tipTimer{};
    //倍率提示框
    RateTip tip;
    //参考边长
    int refX{};
    int refY{};

private slots:

    //刷新图片槽函数
    void updateImage(const QImage &i);

public:
    //缩放倍率>=1
    double scaleRate{1};

    MagnifyRes();

    //设置初始化区域
    void setRect(QRect r);

    //启动刷新放大镜线程
    void launch();

    //设置缩放率
    void setScaleRate(double rate);

    //停止放大镜
    void stop();

protected:
    //绘制事件
    void paintEvent(QPaintEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

private:
    //更新位置大小
    void updateRect();
    //更新工具提示
    void updateTooltip();
    //检查缩放倍率
    void checkRate(double s);
};


#endif //CONCURRENT_TOOLKIT_MAGNIFYRES_H
