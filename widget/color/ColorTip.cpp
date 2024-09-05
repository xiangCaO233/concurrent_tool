//
// Created by 2333 xiang on 2024/9/3.
//

#include <QVBoxLayout>
#include <iostream>
#include "ColorTip.h"
#include "../../App.h"

using namespace std;

ColorTip::ColorTip() : DraggableWidget() {

    layout = new QVBoxLayout;
    layout->setSpacing(2);
    layout->setContentsMargins(2, 2, 2, 0);
    hLayout = new QHBoxLayout;
    hLayout->setSpacing(2);
    hLayout->setContentsMargins(2, 2, 2, 0);
    buttons = new QWidget;

    copyRgba = new QPushButton("rgba");
    copyHex = new QPushButton("hex");



    copyRgba->adjustSize();
    copyHex->adjustSize();
    copyRgba->setFocusPolicy(Qt::NoFocus);
    copyHex->setFocusPolicy(Qt::NoFocus);

    connect(copyRgba, &QPushButton::clicked, [this]() {
        QClipboard *clipboard = QApplication::clipboard();
        QString rgb =QString::number(color.red())+ ","+QString::number(color.green())+","+QString::number(color.blue());
        clipboard->setText(rgb);
        cout << "copy rgba" << endl;
    });
    connect(copyHex, &QPushButton::clicked, [this]() {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(color.name());
        cout << "copy hex" << endl;
    });

    hLayout->addWidget(copyRgba);
    hLayout->addWidget(copyHex);
    buttons->setLayout(hLayout);

    buttons->adjustSize();

    //layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(&posText, 0, Qt::AlignCenter);
    layout->addWidget(&colorText, 0, Qt::AlignCenter);
    layout->addWidget(buttons);

    setLayout(layout);

}

void ColorTip::setColor(const QColor &c, QPoint point) {
    color = c;
    this->pos = point;

    QString colorString = "[";
    QString colorName = color.name();
    colorString.append("<font color=" + colorName + ">");
    colorString.append(colorName);
    colorString.append("</font>");

    colorString.append(",");
    colorString.append("<font color=red>");
    colorString.append(QString::number(color.red()));
    colorString.append("</font>");

    colorString.append(",");
    colorString.append("<font color=green>");
    colorString.append(QString::number(color.green()));
    colorString.append("</font>");

    colorString.append(",");
    colorString.append("<font color=blue>");
    colorString.append(QString::number(color.blue()));
    colorString.append("</font>");
    colorString.append("]");

    colorText.setText(colorString);
    colorText.adjustSize();

    QString posString = "[ X:";
    QString forgeColor = pubRef::dForge.name();
    posString.append("<font color=" + forgeColor + ">");
    posString.append(QString::number(pos.x()) + " , Y:" + QString::number(pos.y()));
    posString.append("</font>");
    posString.append(" ]");

    posText.setText(posString);
    posText.adjustSize();

    adjustSize();
    repaint();

}

void ColorTip::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setPen(pubRef::pink);
    p.setBrush(pubRef::dBack);
    p.drawRect(rect());
}
