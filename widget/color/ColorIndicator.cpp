//
// Created by 2333 xiang on 2024/9/2.
//

#include "ColorIndicator.h"

ColorIndicator::ColorIndicator() : CloseableWidget() {
    tip = new ColorTip;
    connect(receiver, &ColorReceiver::receivedColor, this, &ColorIndicator::updateColor);
    tip->show();
}

void ColorIndicator::updateColor(QColor color, QPoint pos) {
    currentColor = color;
    colorPos = pos;

    tip->setColor(currentColor, pos);

    //设置大小
    resize((int) (rate * 30), (int) (rate * 30));
    repaint();
    fixPos = QPointF(width() / 2.0, ((1 + 1 / rate) * height()));

    //边缘检测
    desPos = pos - fixPos;
    colorRect = QRectF(pos - fixPos, size());
    QPointF p = pos.toPointF();
    // 判断点是否在屏幕范围内
    if (colorRect.x() < 0) {
        //左侧出去了
        fixIndicatorPos(-width() / 2.0, fixPos.y(), p);
    }
    if (colorRect.y() < 0) {
        //顶侧出去了
        fixIndicatorPos(fixPos.x(), -(int) ((1 + 1 / rate) * height()), p);
    }
    if (colorRect.x() + width() > pubRef::poiWidth) {
        //右侧出去了
        fixIndicatorPos(width(), fixPos.y(), p);
    }
    if (colorRect.y() + height() > pubRef::poiHeight) {
        //下侧出去了
        fixIndicatorPos(fixPos.x(), (int) ((1 + 1 / rate) * height()), p);
    }

    //分支提示位置策略
    switch (tipAlignment) {

        case TOP: {
            setTipAtTop();
//            tipPos = desPos - QPoint((tip->width() - width()) / 2, (int) (tip->height() + rate));
            break;
        }
        case RIGHT: {
            setTipAtRight();
            break;
        }
        case BOTTOM: {
            setTipAtBottom();
//            tipPos = desPos - QPoint((tip->width() - width()) / 2, (int) (colorRect.height() + rate));
            break;
        }
        case LEFT: {
            setTipAtLeft();
            break;
        }
    }
    //更新tip首先应显示的区域
    tipRect = QRectF(tipPos, tip->size());
    //修正tip为最合适的位置
    fixTipPos();

    //移动到最合适的位置
    move(desPos.toPoint());
    tip->move(tipPos.toPoint());
    //置顶窗口
    //raise();

    repaint();
}

void ColorIndicator::displayColor() {
    show();
}

void ColorIndicator::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    QSizeF cSize = size().toSizeF() / rate / 1.5;

    //绘制区域小截图
    QRectF capRect = QRectF(
            pos() + fixPos -
            QPointF(cSize.width() / 2.0, cSize.height() / 2.0),
            cSize
    );

    //放大图像
    QImage sImage = CaptureTool::captureRect(capRect);
    CaptureTool::scaleImageSizeByCenter(sImage, rate, false);
    CaptureTool::scaleImageSizeByCenter(sImage, 1.5, false);

    p.drawImage(-3, -3, sImage);

    //边框
    QColor inverseColor = QColor(255 - currentColor.red(), 255 - currentColor.green(), 255 - currentColor.blue());
    p.setPen(QPen(currentColor, rate));
    p.setBrush(Qt::NoBrush);
    p.drawRect(rect());

    //标线
    double bdWidth = rate * 1.5;
    //水平
    drawGradientLine(p, QPointF(1.5 * rate, (height() / 2.0)),
                     QPointF(width() / 2.0 - bdWidth, (height() / 2.0)), currentColor, inverseColor, bdWidth);
    drawGradientLine(p, QPointF(width() - 1.5 * rate, (height() / 2.0)),
                     QPointF(width() / 2.0 + bdWidth, (height() / 2.0)), currentColor, inverseColor, bdWidth);

    //反色中心框
    p.setPen(QPen(inverseColor, bdWidth));
    //中心框
    p.drawRoundedRect(
            QRectF(
                    QPointF(width() / 2.0 - bdWidth, (height() / 2.0) - bdWidth),
                    QSizeF(2 * bdWidth, 2 * bdWidth)),
            bdWidth, bdWidth
    );

    //垂直
    drawGradientLine(p, QPointF((width() / 2.0), 1.5 * rate),
                     QPointF((width() / 2.0), height() / 2.0 - bdWidth), currentColor, inverseColor, bdWidth);
    drawGradientLine(p, QPointF((width() / 2.0), height() - 1.5 * rate),
                     QPointF((width() / 2.0), height() / 2.0 + bdWidth), currentColor, inverseColor, bdWidth);
}

void ColorIndicator::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    // 添加动作到菜单
    QAction *close = menu.addAction(CaptureTool::generateIcon(pubRef::svgs["close"], QSize(24, 24)), "关闭");
    connect(close, &QAction::triggered, this, [this]() {
        delete tip;
        tip = nullptr;
        destroy();

    });

    // 显示菜单
    menu.exec(event->globalPos());
}

void ColorIndicator::fixIndicatorPos(double ax, double ay, QPointF &pos) {
    fixPos.setX(ax);
    fixPos.setY(ay);
    //边缘检测
    desPos = pos - fixPos;
    colorRect = QRectF(desPos, size());

}

void ColorIndicator::fixTipPos() {

    //检测tip本身是否超出屏幕
    if (tipPos.y() < 0 || tipPos.x() < 0) {
        //左上角
        if (desPos.x() < pubRef::poiWidth / 2.0) {
            //整体偏左,放右边
            setTipAtRight();
        } else {
            //整体偏右,放左边
            setTipAtLeft();
        }
    }

    if (tipPos.y() + tipRect.height() > pubRef::poiHeight || tipPos.x() + tipRect.width() > pubRef::poiWidth) {
        //右下角
        if (desPos.x() < pubRef::poiWidth / 2.0) {
            //整体偏左,放右边
            setTipAtRight();
        } else {
            //整体偏右,放左边
            setTipAtLeft();
        }
    }

    tipRect = QRectF(tipPos, tip->size());

}

void ColorIndicator::setTipAtTop() {
    tipPos = desPos - QPointF((tip->width() - width()) / 2.0, (tip->height() + rate));
}

void ColorIndicator::setTipAtRight() {
    tipPos = QPointF(
            desPos.x() + colorRect.width() + rate,
            desPos.y() + (colorRect.height() - tipRect.height()) / 2.0);
}

void ColorIndicator::setTipAtBottom() {
    tipPos = QPointF(
            desPos.x() - ((tip->width() - colorRect.width()) / 2.0),
            desPos.y() + colorRect.height() + rate).toPoint();
}

void ColorIndicator::setTipAtLeft() {
    tipPos = QPointF(
            desPos.x() - tipRect.width() - rate,
            desPos.y() + (colorRect.height() - tipRect.height()) / 2.0).toPoint();
}

void ColorIndicator::drawGradientLine(QPainter &p, QPointF p1, QPointF p2, QColor &c1, QColor &c2, double bw) {
    //设置渐变
    QLinearGradient lg4(p1, p2);
    lg4.setColorAt(0, c1);
    lg4.setColorAt(1, c2);
    p.setPen(QPen(lg4, bw));
    p.drawLine(p1, p2);
}
