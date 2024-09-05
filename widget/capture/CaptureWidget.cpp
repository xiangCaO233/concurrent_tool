//
// Created by 2333 xiang on 2024/8/31.
//

#include <iostream>
#include "CaptureWidget.h"

using namespace std;

CaptureWidget::CaptureWidget() : UndecoratedWidget(), posInfo(QLabel("")), floatImage(QSize(0, 0)) {
    //启用鼠标追踪
    setMouseTracking(true);
    //全屏窗口
    resize(pubRef::poiWidth, pubRef::poiHeight);
    //光标设置
    setCursor(Qt::CursorShape::CrossCursor);
    posInfo.move(-1, -1);
    posInfo.resize((int) ((180 / 1920.0) * pubRef::poiWidth), (int) ((20 / 1080.0) * pubRef::poiHeight));
    posInfo.setParent(this);
    posInfo.show();
    editCapture = false;
}

void CaptureWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    //背景
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(rect(), QColor(39, 40, 41, 120)); // 绿色，透明度50%
    //绘制截图区域
    painter.setPen(Qt::green);
    painter.drawPolygon(capturePath.toFillPolygon());

    painter.setPen(Qt::transparent);
    painter.fillPath(capturePath, QBrush(Qt::transparent));

    QWidget::paintEvent(event);
}

void CaptureWidget::mousePressEvent(QMouseEvent *event) {
    tempPos = event->pos();
    //capturePath.addRect(QRect(tempPos.x(),tempPos.y(),1,1));
    //repaint();
}

void CaptureWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (!capturePath.isEmpty())
        editCapture = false;
}

void CaptureWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget::mouseDoubleClickEvent(event);
    QRectF rect = capturePath.boundingRect();
    QImage image = CaptureTool::captureRect(rect);

    //CaptureTool::scaleImageSizeByCenter(image,(rect.width() / (double )(image.width())));
    cout<<"rect:"<<rect.size().width()<<endl;
    cout<<"image:"<<image.width()<<endl;

    floatImage.resize(rect.toRect().size());
    floatImage.setImage(image);


    floatImage.move(event->pos());
    floatImage.show();
    capturePath.clear();
    repaint();
    hide();
}

void CaptureWidget::mouseMoveEvent(QMouseEvent *event) {
    //鼠标移动事件
    QPoint pos = event->pos();
    posInfo.setText("当前位置:[x:" + QString::number(pos.x()) + ",y:" + QString::number(pos.y()) + "]");
    posInfo.move(event->pos() + QPoint(-10, -30));
    if (event->buttons() & Qt::LeftButton && editCapture) {
        //左键拖动
        //cout << "drag" << endl;
        QPainterPath tempPath;
        auto x = event->position().x();
        auto y = event->position().y();
        tempPath.addRect(QRect(tempPos.x(), tempPos.y(), (int) x - tempPos.x(), (int) y - tempPos.y()));
        capturePath = tempPath;
    }
    repaint();
}

void CaptureWidget::display() {
    editCapture = true;
    show();
}


