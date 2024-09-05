//
// Created by 2333 xiang on 2024/9/4.
//

#ifndef CONCURRENT_TOOLKIT_TRANSLATOR_H
#define CONCURRENT_TOOLKIT_TRANSLATOR_H

#include <QVBoxLayout>
#include <QClipboard>
#include <QApplication>
#include <QMimeData>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include "../template/CloseableWidget.h"
#include "../../tool/CaptureTool.h"
#include "BaiduTranslator.h"
#include "Transer.h"
#include "QThread.h"
#include "QTextEdit"

class Translator : public CloseableWidget {
Q_OBJECT

    QVBoxLayout *rootLayout;

    QWidget *textWidget;
    QHBoxLayout *tLayout;

    QWidget *leftChildWidget;
    QVBoxLayout *leftLangLayout;

    QWidget *rightChildWidget;
    QVBoxLayout *rightLangLayout;

    QComboBox *apiSelection;
    QLabel *title;
    QTextEdit *srcText;
    QTextEdit *desText;
    QComboBox *leftLangSelection;
    QComboBox *rightLangSelection;

    QPushButton *switchSide;
    QPushButton *perform;
    Transer *transer{};

public:
    Translator();

public slots:
    //槽-更新翻译结果(回调)
    void updateDes(const QString &desStr);

protected:
    void paintEvent(QPaintEvent *event) override;

    void contextMenuEvent(QContextMenuEvent *event) override;

    //初始化语言选择器
    static void initLangSelector(QComboBox *comboBox);

    //执行翻译
    void performTranslate();
};


#endif //CONCURRENT_TOOLKIT_TRANSLATOR_H
