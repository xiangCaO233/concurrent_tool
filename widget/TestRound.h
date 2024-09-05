//
// Created by 2333 xiang on 2024/8/28.
//

#ifndef CONCURRENT_TOOLKIT_TESTROUND_H
#define CONCURRENT_TOOLKIT_TESTROUND_H


#include <QWidget>
#include <QPainter>
#include <iostream>
#include <cmath>

class TestRound : public QWidget {
    static double gold;
public:
    explicit TestRound(QWidget *parent) : QWidget(parent) {
        // 去掉窗口边框
        setWindowFlags(Qt::FramelessWindowHint);
        // 设置窗口背景为透明
        //setAttribute(Qt::WA_TranslucentBackground);
        resize(520, 520);
    }


protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
//        //设置笔刷颜色
//        painter.setBrush(Qt::white);
// 设置画笔颜色和宽度
        QPen pen(Qt::black, 2);  // 边框颜色和宽度
        painter.setPen(pen);


        QRect outerRect = rect(); // 获取窗口的矩形区域
        outerRect.adjust(1,1,-1,-1);
        QPoint center = outerRect.center(); // 获取窗口的矩形区域

        int width = outerRect.width();
        int height = outerRect.height();
        painter.drawRect(outerRect);

        painter.setBrush(Qt::white);
        // 绘制扇形部分
        //在 Qt 中，角度是以 1/16 度为单位的
        int startAngle = 30 * 16;   // 起始角度，0度表示3点钟方向
        int spanAngle = 120 * 16;  // 扇形的跨度角度
        painter.drawPie(outerRect, startAngle, spanAngle);

        // 设置笔宽为 2 像素，绘制扇形边界
        painter.setPen(QPen(Qt::red, 2)); // 边界，像素宽度
        painter.drawArc(outerRect, startAngle, spanAngle);

        // 绘制内部遮盖圆（遮盖部分黄金比例）
        QRect innerRect = QRect(
                center.x() - (int)(width * (gold / 2)),
                center.y() - (int)(height * (gold / 2)),
                (int) (width * gold),
                (int) (height * gold)
        );
        innerRect.adjust(-2,-2,2,2);

        painter.setPen(QPen(Qt::black, 2)); // 边界，像素宽度
        painter.drawRect(innerRect);

        painter.drawArc(innerRect, startAngle, spanAngle);

        innerRect.adjust(2,2,-2,-2);
        painter.drawRect(innerRect);
        // 设置组合模式为清除模式，使得内部圆部分透明
        painter.setCompositionMode(QPainter::CompositionMode_Clear);

        painter.drawEllipse(innerRect);

    }

};


#endif //CONCURRENT_TOOLKIT_TESTROUND_H
