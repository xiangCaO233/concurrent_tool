//
// Created by 2333 xiang on 2024/8/28.
//

#ifndef CONCURRENT_TOOLKIT_APP_H
#define CONCURRENT_TOOLKIT_APP_H


#include <QWidget>
#include <QVBoxLayout>
#include "widget/menu/PopMenu.h"
#include "listener/MouseWheelListener.h"
#include "listener/KeyListener.h"
#include "listener/MouseListener.h"
#include <QWindow>
#include <objc/objc.h>
#include <objc/message.h>

class PopMenu;

class KeyListener;

class MouseMotionListener;

class MouseWheelListener;

class App {
public:
    static KeyListener keyListener;
    static MouseListener mouseListener;
    static MouseMotionListener motionListener;
    static MouseWheelListener wheelListener;
    static PopMenu *pm;
    static QPoint pos;

    static void start(int x, int y);

    static void initial();

    static void forceActivateWindow(QWidget *widget);
};


#endif //CONCURRENT_TOOLKIT_APP_H
