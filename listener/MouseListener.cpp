//
// Created by 2333 xiang on 2024/8/28.
//

#include "MouseListener.h"
#include "KeyListener.h"
#include "QTimer"

#include "../App.h"
#include "iostream"

using namespace std;

void MouseListener::onPress(const PointerEvent &e) {

    int x = (int) e.getCoordinate().x;
    int y = (int) e.getCoordinate().y;

    if (App::pm) {
        //检测并隐藏本体
        int translateX = App::pm->pos().x();
        int translateY = App::pm->pos().y();
        QPainterPath region = App::pm->path.translated(translateX,translateY);
        if (!region.contains(QPoint(x, y))) {
            QMetaObject::invokeMethod(App::pm, "hide", Qt::QueuedConnection);
        }
    }


}

void MouseListener::onRelease(const PointerEvent &e) {

}

void MouseListener::onClicked(const PointerEvent &e) {

}

void MouseListener::onDragged(const PointerEvent &e) {

}
