//
// Created by 2333 xiang on 2024/9/2.
//

#include <iostream>
#include <QToolTip>
#include "MagnifyRes.h"
#include "../tool/PublicReferences.h"

using namespace std;

MagnifyRes::MagnifyRes() : DraggableWidget(), updater(new ZoomUpdater()) {
    //启用鼠标追踪
    setMouseTracking(true);
}

void MagnifyRes::paintEvent(QPaintEvent *event) {
    //绘制图片
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.drawImage(0, 0, image);
}

void MagnifyRes::setRect(QRect r) {
    updater->zoomRegion = r;
    refX = r.width();
    refY = r.height();
    updateRect();

}

void MagnifyRes::updateImage(const QImage &i) {
    image = i;
    repaint();
}

void MagnifyRes::setScaleRate(double rate) {
    checkRate(rate);
    updater->scaleRate = scaleRate;
    updateRect();
}

void MagnifyRes::launch() {
    //启动放大线程
    auto *thread = new QThread;
    // 将 更新器 移动到新线程
    updater->moveToThread(thread);

    // 连接信号和槽
    //启动线程后执行zoom
    QObject::connect(thread, &QThread::started, updater, &ZoomUpdater::zoom);
    //更新器销毁时退出线程
    QObject::connect(updater, &MagnifyRes::destroyed, thread, &QThread::quit);
    //将更新器的信号连接到此处更新
    connect(updater, &ZoomUpdater::callRender, this, &MagnifyRes::updateImage);
    //当线程结束或退出时自动销毁
    QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    // 启动线程
    thread->start();
    move(250, 70);
}

void MagnifyRes::updateRect() {
    checkRate(scaleRate);
    resize((int) (refX * scaleRate), (int) (refY * scaleRate));
}

void MagnifyRes::keyPressEvent(QKeyEvent *event) {
    if (event->text() == QString("=")) {
        setScaleRate(scaleRate + 0.25);
        updateTooltip();
    }
    if (event->text() == QString("-")) {
        setScaleRate(scaleRate - 0.25);
        updateTooltip();
    }


}

void MagnifyRes::mouseMoveEvent(QMouseEvent *event) {
    DraggableWidget::mouseMoveEvent(event);
    currentPos = event->pos();
}

void MagnifyRes::stop() {
    updater->stop();
    hide();
}

void MagnifyRes::wheelEvent(QWheelEvent *event) {
    setScaleRate(scaleRate + (event->pixelDelta().y() / 100.0));
    updateTooltip();
}

void MagnifyRes::resizeEvent(QResizeEvent *event) {

}

void MagnifyRes::updateTooltip() {
    // 动态生成提示信息内容
    QString tooltipText = QString("%3x").arg(scaleRate);
    tip.setText(tooltipText);
    QPoint refP = QPoint(tip.width()+2, tip.height()+2);
    //计算相对坐标
    tip.move(pos() + currentPos - refP);
    //显示并抬升到顶部
    if (!tip.isVisible()) tip.show();
    tip.raise();

    //更新计时器显示1秒
    if (!tipTimer) {
        tipTimer = new QTimer(this);
        connect(tipTimer, &QTimer::timeout, this, [this]() {
            tip.hide();
        });
    }
    tipTimer->start(1000);

}

void MagnifyRes::checkRate(double s) {
    double maxRate = min(((pubRef::poiHeight - refY) / (double) refY), ((pubRef::poiWidth - refX) / (double) refX));
    cout<<"源："<<s<<endl;
    if (s > maxRate) s = maxRate;
    if (s < 1) s = 1;
    cout<<"修正："<<s<<endl;
    scaleRate = s;
}

