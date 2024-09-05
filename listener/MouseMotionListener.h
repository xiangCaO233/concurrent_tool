//
// Created by 2333 xiang on 2024/8/28.
//  鼠标移动监听器
//

#ifndef CONCURRENT_TOOLKIT_MOUSEMOTIONLISTENER_H
#define CONCURRENT_TOOLKIT_MOUSEMOTIONLISTENER_H

#include "pointer/listener/PointerMotionListener.h"
#include "../App.h"
#include "../tool/CaptureTool.h"

class MouseMotionListener : public PointerMotionListener {
public:
    void onMove(const PointerEvent &e) override;

    void onDrag(const PointerEvent &e) override;

};

#endif //CONCURRENT_TOOLKIT_MOUSEMOTIONLISTENER_H
