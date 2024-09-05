//
// Created by 2333 xiang on 2024/9/1.
//

#include <iostream>
#include <QMessageBox>
#include "FloatImage.h"
#include "../tool/CaptureTool.h"
#include "../tool/PublicReferences.h"

FloatImage::FloatImage(QSize size) {
    resize(size);
}

FloatImage::FloatImage(QImage &imageSource) : DraggableWidget() {
    // 设置窗口置顶
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    setImage(imageSource);
}

void FloatImage::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(pubRef::pink);
    p.setPen(pen);
    p.drawRect(rect().adjusted(1, 1, -1, -1));
    p.drawImage(2, 2, displayImage);

}

void FloatImage::setImage(QImage &image) {
    //保存源图
    srcImage = image;
    //拷贝一份用于显示
    displayImage = image.copy();
    //增加尺寸以画完整图
    setFixedSize(size() + QSize(4, 4));
    repaint();
}

void FloatImage::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    // 添加动作到菜单
    QAction *copyAndClose = menu.addAction("复制并关闭");
    QAction *copy = menu.addAction(CaptureTool::generateIcon(pubRef::svgs["copy"], QSize(24, 24)), "复制");
    QAction *close = menu.addAction(CaptureTool::generateIcon(pubRef::svgs["close"], QSize(24, 24)), "关闭");

    // 连接动作的槽函数
    connect(copyAndClose, &QAction::triggered, this, [this]() {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setImage(srcImage);
        hide();
        std::cout << "已复制到剪切版" << std::endl;
    });

    connect(copy, &QAction::triggered, this, [this]() {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setImage(srcImage);
        std::cout << "已复制到剪切版" << std::endl;
    });

    connect(close, &QAction::triggered, this, [this]() {
        hide();
    });

    // 显示菜单
    menu.exec(event->globalPos());
}


