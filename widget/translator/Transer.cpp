//
// Created by 2333 xiang on 2024/9/5.
//

#include "Transer.h"
Transer::Transer()  : QObject(nullptr),bdtrslt(new BaiduTranslator("20240905002141514", "ZN_BP_xiWTT5MnRsQ14V")){

}

void Transer::doTranslate(const QString &from,const QString &to,const QString& sourceText) {
    std::string res = bdtrslt->translate(from.toStdString(),to.toStdString(),sourceText.toStdString());
    emit done(QString::fromStdString(res));
}


