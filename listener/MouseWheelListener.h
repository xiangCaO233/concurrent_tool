//
// Created by 2333 xiang on 2024/8/31.
//

#ifndef CONCURRENT_TOOLKIT_MOUSEWHEELLISTENER_H
#define CONCURRENT_TOOLKIT_MOUSEWHEELLISTENER_H
#include "pointer/listener/PointerWheelListener.h"
#include "../widget/menu/PopMenu.h"


class MouseWheelListener: public PointerWheelListener{
public:
    void onScroll(const PointerWheelEvent &e) override;

    void onScrolled(const PointerWheelEvent &e) override;
};


#endif //CONCURRENT_TOOLKIT_MOUSEWHEELLISTENER_H
