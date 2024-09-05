//
// Created by 2333 xiang on 2024/9/4.
//  屏幕标尺工具
//

#ifndef CONCURRENT_TOOLKIT_SCREENRULER_H
#define CONCURRENT_TOOLKIT_SCREENRULER_H
#include "../template/CloseableWidget.h"

class ScreenRuler : public CloseableWidget{
public:
    ScreenRuler();

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
};


#endif //CONCURRENT_TOOLKIT_SCREENRULER_H
