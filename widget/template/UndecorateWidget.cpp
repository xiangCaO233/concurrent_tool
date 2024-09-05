//
// Created by 2333 xiang on 2024/9/1.
//

#include "UndecoratedWidget.h"

UndecoratedWidget::UndecoratedWidget(): QWidget(nullptr) {
    // 去掉窗口边框
    setWindowFlags(Qt::FramelessWindowHint);
    // 设置窗口背景为透明
    setAttribute(Qt::WA_TranslucentBackground);
    // 设置窗口置顶
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}