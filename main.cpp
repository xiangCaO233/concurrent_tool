#include <QApplication>
#include "GlobalScreen.h"
#include "App.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    GlobalScreen::startListen();
    //添加监听
    GlobalScreen::globalScreenVal.addKeyListener(App::keyListener);
    GlobalScreen::globalScreenVal.addPointerListener(App::mouseListener);
    GlobalScreen::globalScreenVal.addPointerMotionListener(App::motionListener);
    GlobalScreen::globalScreenVal.addPointerWheelListener(App::wheelListener);
    return QApplication::exec();
}

