//
// Created by 2333 xiang on 2024/8/28.
//

#ifndef CONCURRENT_TOOLKIT_KEYLISTENER_H
#define CONCURRENT_TOOLKIT_KEYLISTENER_H

#include "GlobalScreen.h"
#include "keyboard//KeyMaps.h"
#include "QApplication"

#include <iostream>
#include <unordered_map>

#include "../App.h"

class KeyListener : public KeyboardListener, public QObject {
public:
    //按下
    void onPress(const KeyboardEvent &e) override;

    //释放
    void onRelease(const KeyboardEvent &e) override;

    //按了
    void onPressed(const KeyboardEvent &e) override;

private:
    static void sendIndicateColor(int dx,int dy);
    static void hideIndicator();
};


#endif //CONCURRENT_TOOLKIT_KEYLISTENER_H
