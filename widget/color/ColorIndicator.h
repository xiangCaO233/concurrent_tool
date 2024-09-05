//
// Created by 2333 xiang on 2024/9/2.
//

#ifndef CONCURRENT_TOOLKIT_COLORINDICATOR_H
#define CONCURRENT_TOOLKIT_COLORINDICATOR_H

#include <QLabel>
#include "../template/CloseableWidget.h"
#include "../../listener/MouseListener.h"
#include "../../App.h"
#include "ColorReceiver.h"
#include "ColorTip.h"

class ColorIndicator : public CloseableWidget {

    QColor currentColor;
    ColorReceiver *receiver = new ColorReceiver;
    double rate = 10.0;
    QPointF colorPos;
    //本体修正位置
    QPointF fixPos;
    //提示
    ColorTip *tip;
    //本体目标位置
    QPointF desPos;
    //本体区域
    QRectF colorRect;
    //提示位置
    QPointF tipPos;
    //提示区域
    QRectF tipRect;
    //提示对其策略
    TipAlignment tipAlignment = TipAlignment::TOP;

    friend class MouseMotionListener;
    friend class KeyListener;
    friend class PopMenu;

public slots:
    void updateColor(QColor color, QPoint pos);

public:
    ColorIndicator();
    ~ColorIndicator() override{
        std::cout<<"release indicator"<<std::endl;
        delete tip;
    };

    void displayColor();

protected:
    void paintEvent(QPaintEvent *event) override;

    void contextMenuEvent(QContextMenuEvent *event) override;


private:
    void fixIndicatorPos(double ax, double ay, QPointF &pos);

    void fixTipPos();

    void setTipAtTop();

    void setTipAtRight();

    void setTipAtBottom();

    void setTipAtLeft();

    static void drawGradientLine(QPainter &p, QPointF p1, QPointF p2, QColor &c1, QColor &c2, double bw);
};


#endif //CONCURRENT_TOOLKIT_COLORINDICATOR_H
