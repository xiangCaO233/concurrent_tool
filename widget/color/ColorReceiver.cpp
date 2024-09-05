//
// Created by 2333 xiang on 2024/9/3.
//

#include "ColorReceiver.h"

void ColorReceiver::receiveColor(QColor color,QPoint pos) {
    emit receivedColor(color,pos);
}
