//
// Created by 2333 xiang on 2024/8/28.
//
#include "MouseMotionListener.h"
#include "iostream"

using namespace std;

void MouseMotionListener::onMove(const PointerEvent &e) {
//    cout<<"鼠标移动->";
//    cout<<"[x="<<e.getCoordinate().x<<", y="<<e.getCoordinate().y<<"]"<<endl;
//检查并发送像素
//    App::pos = QPoint((int)e.getCoordinate().x,(int)e.getCoordinate().y);
    if (App::pm){

        //cout<<&c<<endl;
        if (App::pm->colorIndicator) {
            QPoint p = QPoint((int) e.getCoordinate().x, (int) e.getCoordinate().y);
            App::pm->colorIndicator->receiver->receiveColor(
                    CaptureTool::getScreenPixelColor(p), p);
        }
    }

//            QMetaObject::invokeMethod(App::pm,"updatePos",Qt::QueuedConnection);}


}

void MouseMotionListener::onDrag(const PointerEvent &e) {

}

