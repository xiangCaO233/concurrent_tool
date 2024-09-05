//
// Created by 2333 xiang on 2024/9/3.
//

#ifndef CONCURRENT_TOOLKIT_COLORTIP_H
#define CONCURRENT_TOOLKIT_COLORTIP_H

#include <QLabel>
#include <QColor>
#include <QPushButton>
#include "../template/DraggableWidget.h"

enum TipAlignment{
    TOP,RIGHT,BOTTOM,LEFT
};

class ColorTip : public DraggableWidget{
    QLabel posText;
    QLabel colorText;
    QColor color;
    QPoint pos;

    QVBoxLayout *layout;
    QWidget *buttons;
    QHBoxLayout *hLayout;
    QPushButton *copyRgba;
    QPushButton *copyHex;
public:
    ColorTip();
    ~ColorTip() override{
        std::cout<<"release tip"<<std::endl;
    };
    void setColor(const QColor& c,QPoint point);

protected:
    void paintEvent(QPaintEvent *event) override;
};


#endif //CONCURRENT_TOOLKIT_COLORTIP_H
