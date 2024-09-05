//
// Created by 2333 xiang on 2024/9/3.
//

#ifndef CONCURRENT_TOOLKIT_RATETIP_H
#define CONCURRENT_TOOLKIT_RATETIP_H

#include <QLabel>
#include "../template/UndecoratedWidget.h"


class RateTip : public UndecoratedWidget{
    QLabel text;
public:
    RateTip();
    void setText(const QString& str);

protected:
    void paintEvent(QPaintEvent *event) override;
};


#endif //CONCURRENT_TOOLKIT_RATETIP_H
