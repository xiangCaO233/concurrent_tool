//
// Created by 2333 xiang on 2024/9/2.
//

#ifndef CONCURRENT_TOOLKIT_ZOOMUPDATER_H
#define CONCURRENT_TOOLKIT_ZOOMUPDATER_H


#include <QObject>
#include <QImage>
#include <QRectF>


class ZoomUpdater : public QObject{
    Q_OBJECT
public:
    //放大的区域
    QRectF zoomRegion;
    //缩放倍率>=1
    double scaleRate{1};
    //线程标识
    bool run = true;

    void stop();
signals:
    void callRender(QImage image);

public slots:

    void zoom();

};


#endif //CONCURRENT_TOOLKIT_ZOOMUPDATER_H
