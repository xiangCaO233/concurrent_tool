//
// Created by 2333 xiang on 2024/9/3.
//

#include <QVBoxLayout>
#include <iostream>
#include "RateTip.h"
#include "../../App.h"

using namespace std;

RateTip::RateTip() : UndecoratedWidget() {
    QVBoxLayout layout;
    layout.addWidget(&text);
    setLayout(&layout);

}

void RateTip::setText(const QString &str) {
    text.setText(str);
    text.adjustSize();
    resize(text.size());
    repaint();
    //App::forceActivateWindow(this);
}

void RateTip::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setPen(pubRef::pink);
    p.setBrush(pubRef::dBack);
    p.drawRect(rect());
}
