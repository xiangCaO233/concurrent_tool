//
// Created by 2333 xiang on 2024/9/4.
//

#include "CloseableWidget.h"
#include "../../tool/CaptureTool.h"
#include "../../tool/PublicReferences.h"
#include "../color/ColorIndicator.h"

void CloseableWidget::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    // 添加动作到菜单
    QAction *close = menu.addAction(CaptureTool::generateIcon(pubRef::svgs["close"],QSize(24,24)),"关闭");
    connect(close, &QAction::triggered, this, [this]() {
        auto* derived = dynamic_cast<ColorIndicator*>(this);
        delete derived;
    });

    // 显示菜单
    menu.exec(event->globalPos());
}
