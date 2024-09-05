//
// Created by 2333 xiang on 2024/9/5.
//

#ifndef CONCURRENT_TOOLKIT_TRANSER_H
#define CONCURRENT_TOOLKIT_TRANSER_H


#include <QObject>
#include <QString>
#include <utility>
#include "BaiduTranslator.h"


class Transer : public QObject {
Q_OBJECT
    BaiduTranslator *bdtrslt;
public:
    explicit Transer();

public slots:
    //开始翻译信号
    void doTranslate(const QString &from,const QString &to,const QString& sourceText);

signals:
    //完成翻译信号->Translator::updateDes槽
    void done(const QString &result);
};


#endif //CONCURRENT_TOOLKIT_TRANSER_H
