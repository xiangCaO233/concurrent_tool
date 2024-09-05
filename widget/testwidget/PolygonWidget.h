//
// Created by 2333 xiang on 2024/9/1.
//

#ifndef CONCURRENT_TOOLKIT_POLYGONWIDGET_H
#define CONCURRENT_TOOLKIT_POLYGONWIDGET_H

#include "../../tool/PublicReferences.h"
#include "../template/UndecoratedWidget.h"


class PolygonWidget : public UndecoratedWidget {
    QPainterPath polygonPath;
public:
    explicit PolygonWidget();

    void setPath(QPainterPath path);

protected:
    void paintEvent(QPaintEvent *event) override;
};


#endif //CONCURRENT_TOOLKIT_POLYGONWIDGET_H
