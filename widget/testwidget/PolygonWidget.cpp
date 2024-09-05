//
// Created by 2333 xiang on 2024/9/1.
//

#include "PolygonWidget.h"
#include "../../App.h"

#include <utility>

PolygonWidget::PolygonWidget() : UndecoratedWidget() {
    //全屏
    resize(pubRef::poiWidth, pubRef::poiHeight);
}

void PolygonWidget::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::blue);
    qDebug() << "draw polygon" << "\n";
    qDebug() << "polygon size:" << polygonPath.elementCount() << "\n";


    // 使用 QPainterPathStroker 扩展路径
    QPainterPathStroker stroker;
    stroker.setWidth(1); // 控制边缘宽度
    stroker.setCapStyle(Qt::RoundCap); // 圆形端点
    stroker.setJoinStyle(Qt::RoundJoin); // 圆形连接
    QPainterPath extendedPath = stroker.createStroke(polygonPath);
//    QRadialGradient gradient(path.elementAt(1),10); // 以原点为中心的径向渐变
//
//    gradient.setColorAt(0, pubRef::dBack);
//    gradient.setColorAt(1, Qt::white);

    p.drawPath(extendedPath);

}

void PolygonWidget::setPath(QPainterPath path) {
    int translateX = App::pos.x();
    int translateY = App::pos.y();
    path.translate(translateX, translateY);
    polygonPath = path;
    repaint();
}
