//
// Created by 2333 xiang on 2024/8/28.
//

#ifndef CONCURRENT_TOOLKIT_MOUSELISTENER_H
#define CONCURRENT_TOOLKIT_MOUSELISTENER_H

#include "pointer/listener/PointerListener.h"
#include "../tool/CaptureTool.h"

class MouseListener : public PointerListener {

public:
    //按下
    void onPress(const PointerEvent &e) override;

    //释放
    void onRelease(const PointerEvent &e) override;

    //点击
    void onClicked(const PointerEvent &e) override;

    //拖动完成
    void onDragged(const PointerEvent &e) override;

};


#endif //CONCURRENT_TOOLKIT_MOUSELISTENER_H
