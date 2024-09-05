//
// Created by 2333 xiang on 2024/8/28.
//

#include "App.h"

KeyListener App::keyListener;
MouseListener App::mouseListener;
MouseMotionListener App::motionListener;
MouseWheelListener App::wheelListener;
PopMenu *App::pm = nullptr;
QPoint App::pos(0, 0);

void App::start(int x, int y) {
    delete pm;
    initial();
    pm->show();
}

//macos置顶api
void App::forceActivateWindow(QWidget *widget) {
    if (!widget) return;
    QSize size = widget->size();
    // 获得窗口句柄
    WId wid = widget->winId();
    QWindow *window = QWindow::fromWinId(wid);
    if (!window) return;

    // 获取 NSApplication sharedApplication
    Class nsApplicationClass = objc_getClass("NSApplication");
    SEL sharedApplicationSelector = sel_registerName("sharedApplication");
    auto (*sharedApplicationFunc)(Class, SEL) = reinterpret_cast<id (*)(Class, SEL)>(objc_msgSend);
    id app = sharedApplicationFunc(nsApplicationClass, sharedApplicationSelector);

    // 调用 activateIgnoringOtherApps: 方法
    SEL activateIgnoringOtherAppsSelector = sel_registerName("activateIgnoringOtherApps:");
    auto (*activateIgnoringOtherAppsFunc)(id, SEL, BOOL) = reinterpret_cast<void (*)(id, SEL, BOOL)>(objc_msgSend);

    activateIgnoringOtherAppsFunc(app, activateIgnoringOtherAppsSelector, YES);

    // 调用 Qt 的 raise 和 activateWindow 方法
    widget->raise();
    widget->activateWindow();
    widget->setFocus();
    widget->resize(size);
    widget->move(pos);
    widget->update();
    widget->repaint();
}

void App::initial() {
    pm = new PopMenu(0, 0);
}


