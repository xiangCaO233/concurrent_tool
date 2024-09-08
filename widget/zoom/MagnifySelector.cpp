//
// Created by 2333 xiang on 2024/9/2.
//

#include "MagnifySelector.h"
#include "iostream"

using namespace std;

MagnifySelector::MagnifySelector(QRect rect) : DraggableWidget() {
    //边框宽度 宽左右各加一个边框宽度，上加三个边框宽度，下加一个边框宽度
    resize(rect.size() + QSize(2 * borderSize, 4 * borderSize));
    move(rect.topLeft() - QPoint(borderSize, 3 * borderSize));

    magnifyRes.setRect(rect);
    magnifyRes.launch();

}

void MagnifySelector::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPen pen1(pubRef::dForge, 1);
    painter.setPen(pen1);
    painter.setBrush(pubRef::pink);

    //拖动钮
    painter.drawRoundedRect(dragRect, 4, 4);

    //设置笔粗为边框宽度
    QPen pen(pubRef::pink, borderSize);
    painter.setBrush(Qt::NoBrush);

    painter.setPen(pen);
    //绘制圆角矩形
    QRect dRect = rect().adjusted((int) (0.5 * borderSize), (int) (2.5 * borderSize), (int) (-0.5 * borderSize),
                                  (int) (-0.5 * borderSize));
    painter.drawRoundedRect(dRect, 0.2, 0.2);
    painter.setPen(Qt::NoPen);

    painter.setPen(QPen(pubRef::dBack, 3));
    for (int i = 0; i < 3; i++) {
        int sx = (width() - 5 * borderSize) / 2 + borderSize;
        int length = 3 * borderSize;
        int y = borderSize / 2 + i * borderSize;
        painter.drawLine(QPoint(sx, y), QPoint(sx + length, y));
    }

//    painter.drawRect()
}

void MagnifySelector::mousePressEvent(QMouseEvent *event) {
    DraggableWidget::mousePressEvent(event);
    isin = dragRect.contains(tempPos);
}


void MagnifySelector::showZoom() {
    magnifyRes.show();
    magnifyRes.move(pos() + QPoint(width(),0));
}

void MagnifySelector::mouseMoveEvent(QMouseEvent *event) {
    if (isin) {
        move(pos().x() + event->pos().x() - tempPos.x(), pos().y() + event->pos().y() - tempPos.y());
    }
}

void MagnifySelector::resizeEvent(QResizeEvent *event) {
    updateDragRec();
    updateResRec();
}


void MagnifySelector::updateDragRec() {
    dragRect = rect().adjusted(
            (int) (width() / 2.0 - 2.5 * borderSize), 0,
            -(int) ((width() / 2.0 - 2.5 * borderSize)),
            -(height() - 3 * borderSize + 1)
    );
}

void MagnifySelector::moveEvent(QMoveEvent *event) {
    updateResRec();
}

void MagnifySelector::updateResRec() {
    magnifyRes.setRect(
            QRect(pos() + QPoint(borderSize, 3 * borderSize),
                  size() - QSize(2 * borderSize, 4 * borderSize)));
}

void MagnifySelector::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    QAction *stop = menu.addAction(CaptureTool::generateIcon(pubRef::svgs["close"], QSize(24, 24)), "停止");
    // 连接动作的槽函数
    connect(stop, &QAction::triggered, this, [this]() {
        QMetaObject::invokeMethod(this, [this]() {
            magnifyRes.stop();
            hide();
        }, Qt::QueuedConnection);
    });
    // 显示菜单
    menu.exec(event->globalPos());
}



