//
// Created by 2333 xiang on 2024/8/29.
//

#ifndef CONCURRENT_TOOLKIT_PUBLICREFERENCES_H
#define CONCURRENT_TOOLKIT_PUBLICREFERENCES_H

#include <QRect>
#include <ApplicationServices/ApplicationServices.h>
#include <QColor>
#include <string>
#include <map>
#include <QString>

class pubRef {
public:
    static double gold;//黄金分割比例
    // 获取主显示器的 ID
    static CGDirectDisplayID displayID;

    // 像素单位宽高
    static int pixWidth;
    static int pixHeight;

    // 像素单位尺寸
    static QRect pixSize;

    //参考尺寸
    static int size;//(1~10)
    static QSize menuSize;

    //参考位置
    static double startPos;
    static double displayCount;

    // 点单位尺寸
    static CGRect displayBounds;

    // 点单位宽高
    static int poiWidth;
    static int poiHeight;

    // 背景色
    static QColor dBack;
    static QColor lBack;
    static QColor dForge;
    static QColor lForge;
    static QColor pink;
    static QColor green;
    static QColor lightGray;

    // svg 映射表
    static std::map<std::string, QString> svgs;
};

#endif //CONCURRENT_TOOLKIT_PUBLICREFERENCES_H