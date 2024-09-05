//
// Created by 2333 xiang on 2024/9/3.
//

#ifndef CONCURRENT_TOOLKIT_COLORRECEIVER_H
#define CONCURRENT_TOOLKIT_COLORRECEIVER_H


#include <QObject>
#include <QColor>
#include <QPoint>

class ColorReceiver : public QObject{
Q_OBJECT
signals:
    void receivedColor(QColor color,QPoint pos);

public:
    void receiveColor(QColor color,QPoint pos);
};


#endif //CONCURRENT_TOOLKIT_COLORRECEIVER_H
