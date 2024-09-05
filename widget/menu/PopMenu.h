//
// Created by 2333 xiang on 2024/8/29.
//

#ifndef CONCURRENT_TOOLKIT_POPMENU_H
#define CONCURRENT_TOOLKIT_POPMENU_H


#include <QSvgRenderer>
#include <QWheelEvent>
#include <QMouseEvent>
#include <iostream>
#include <vector>
#include <string>
#include "../template/UndecoratedWidget.h"
#include "../../tool/CaptureTool.h"
#include "../../tool/PublicReferences.h"

#include "../../tool/PublicReferences.h"
#include "../capture/CaptureWidget.h"
#include "../zoom/MagnifySelector.h"
#include "../color/ColorIndicator.h"
#include "../translator/Translator.h"
#include "../ruler/ScreenRuler.h"
#include "../testwidget/PolygonWidget.h"
#include "../../listener/MouseMotionListener.h"
#include "../../listener/MouseListener.h"


class MagnifySelector;

class ColorIndicator;

class PopMenu : public UndecoratedWidget {
    qreal progress = 0;//0~1
    static std::vector<std::string> functions;//功能列表
    std::unordered_map<std::string, QRectF> funcRecs;//功能位置(实时更新)
    std::unordered_map<std::string, bool> hoveredFunc;//功能位置(实时更新)
    static std::string runningFunc;

    double startAngle = pubRef::startPos * 16;   // 起始角度，0度表示3点钟方向
    double spanAngle = pubRef::displayCount * 30 * 16;  // 扇形的跨度角度
    QRectF ellipse1;
    QRectF ellipse2;
    //鼠标当前位置
    QPointF current;
    //截图窗口
    CaptureWidget captureWidget;
    //放大镜窗口
    MagnifySelector *magWidget{};
    //测试窗口
    PolygonWidget polygonWidget;
    //颜色标记器(公开以便全局监听发送颜色信息)
    ColorIndicator *colorIndicator{};
    //悬浮的标记器（停止重绘）
    ColorIndicator *floatIndicator{};
    //标尺
    ScreenRuler *ruler{};
    //翻译器
    Translator *translator{};
    // QPainterPath (记录相对计算绘制的部分)
    QPainterPath path;
    //  记录实际绘制的部分
    QPainterPath displayPath;

    friend class MouseMotionListener;

    friend class KeyListener;

    friend class MouseWheelListener;

    friend class MouseListener;

public:
    PopMenu(int x, int y);

    ~PopMenu() override;


    //获取滚动进度
    [[nodiscard]] double getProgress() const;

    //设置滚动进度
    void setProgress(double val);

    void capColor();


protected:
    //绘图事件
    void paintEvent(QPaintEvent *event) override;

    // 鼠标滚轮事件
    void wheelEvent(QWheelEvent *event) override;

    // 重写鼠标按下事件
    void mousePressEvent(QMouseEvent *event) override;

    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event) override;

    //绘制功能键
    void paintFuncs(QPainter &p, QRect rect);

private:
    void generatePainterPath();

    void hoverDetect();
};

#endif //CONCURRENT_TOOLKIT_POPMENU_H
