//
// Created by 2333 xiang on 2024/8/28.
//

#include "KeyListener.h"

using namespace std;

void KeyListener::onPress(const KeyboardEvent &e) {
    int keycode = e.getRawKeyCode();
    if (App::pm) {
        if (App::pm->colorIndicator) {
            if (static_cast<int>(KeyType::KEY_ARROW_UP) == keycode) {
                sendIndicateColor(0, -1);
            }
            if (static_cast<int>(KeyType::KEY_ARROW_RIGHT) == keycode) {
                sendIndicateColor(1, 0);
            }
            if (static_cast<int>(KeyType::KEY_ARROW_DOWN) == keycode) {
                sendIndicateColor(0, 1);
            }
            if (static_cast<int>(KeyType::KEY_ARROW_LEFT) == keycode) {
                sendIndicateColor(-1, 0);
            }
        }
    }
}

void KeyListener::onRelease(const KeyboardEvent &e) {
}

void KeyListener::onPressed(const KeyboardEvent &e) {
    int keycode = e.getRawKeyCode();

    //f1
    if (keycode == 122) {
        //获取当前鼠标位置
        CGPoint mousePosition = CGEventGetLocation(CGEventCreate(nullptr));
        App::pos = QPoint((int) (mousePosition.x - pubRef::menuSize.width() / 2.0),
                          (int) (mousePosition.y - pubRef::menuSize.height() / 2.0));
        //显示窗口
        QMetaObject::invokeMethod(this, []() {
            App::start(App::pos.x(), App::pos.y());
            App::forceActivateWindow(App::pm);
        }, Qt::QueuedConnection);

    }


    if (keycode == 53) {
        //esc
        if (App::pm) {
            if (App::pm->colorIndicator) {
                hideIndicator();
            }
        }
    }

    if (keycode == 36) {
        //enter（标记）
        if (App::pm)
            if (App::pm->colorIndicator) {
                QMetaObject::invokeMethod(App::pm, []() {
                    App::pm->capColor();
                    hideIndicator();
                }, Qt::QueuedConnection);
            }

    }

}

void KeyListener::sendIndicateColor(int dx, int dy) {
    QPointF p = App::pm->colorIndicator->colorPos + QPointF(dx, dy);
    App::pm->colorIndicator->receiver->receivedColor(CaptureTool::getScreenPixelColor(p.toPoint()), p.toPoint());
    QMetaObject::invokeMethod(App::pm->colorIndicator, "raise", Qt::QueuedConnection);
}

void KeyListener::hideIndicator() {
    QMetaObject::invokeMethod(App::pm->colorIndicator->tip, "hide", Qt::QueuedConnection);
    QMetaObject::invokeMethod(App::pm->colorIndicator, "hide", Qt::QueuedConnection);
}

