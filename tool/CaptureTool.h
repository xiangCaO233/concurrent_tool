//
// Created by 2333 xiang on 2024/8/29.
//

#ifndef CONCURRENT_TOOLKIT_CAPTURETOOL_H
#define CONCURRENT_TOOLKIT_CAPTURETOOL_H

#include <ApplicationServices/ApplicationServices.h>
#include <QRect>
#include <QIcon>
#include <QColor>
#include <QPainter>
#include <vector>
#include <string>
#include <QImage>
#include <QSvgRenderer>
#include <QApplication>

class CaptureTool {
public:
    //将CGImage转化为QImage
    static QImage CGImageToQImage(CGImageRef i);
    //从指定区域获取屏幕截图
    static CGImageRef getCaptureFromRect(int x, int y, int w, int h);

    static QImage captureRect(QRectF &rect);

    static CGImageRef getCaptureFromRect(QRect &srcRect);

    //获取指定一点的图像1*1
    static CGImageRef getCaptureFromPoint(int x, int y);

    static CGImageRef getCaptureFromPoint(QPoint &srcPoint);

    //获取整个屏幕的截图
    static CGImageRef getCapture();

    //获取指定点的像素颜色
    static QColor getColorAtPoint(int x, int y);
    static QColor getScreenPixelColor(const QPoint &point);

    //创建指定大小的图像缓存
    static QImage creatImage(int x, int y);

    static QImage creatImage(QSize &size);

    //中心旋转
    static QImage rotateByCenter(QImage &image, qreal rotation);

    static QImage rotateImage(QImage &image, qreal rotation);

    //移动图像内容
    static QImage moveImageContents(QImage &image, double dx, double dy);

    static QImage moveImageContents(QImage &image, int dx, int dy);


    static QImage generateImage(const QString &svgPath, const QSize &size, const QColor &color);

    static QImage adjustImageSize(QImage &image, int dx, int dy);

    static QImage adjustImageSizeByCenter(QImage &image, int dx, int dy);

    static QImage scaleImageSizeByCenter(QImage &image, double scale,bool isSmooth);

    static QIcon generateIcon(QString &svg,QSize size);
private:
    static CGImageRef getCaptureFromRect(CGRect &rect);
};


#endif //CONCURRENT_TOOLKIT_CAPTURETOOL_H
