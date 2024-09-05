//
// Created by 2333 xiang on 2024/9/5.
//

#ifndef BAIDUTRANSLATE_TRANSLATECONNECTION_H
#define BAIDUTRANSLATE_TRANSLATECONNECTION_H

#include "iostream"
#include <json/json.h>
#include "BaiduUserInfo.h"
#include "BaiduTranslator.h"
#include "CodeUtil.h"

class TranslateConnection {
    //百度用户信息
    BaiduUserInfo *info;

    //curl连接
    CURL *curl{curl_easy_init()};

    //请求响应
    std::string response;

    //请求回调函数
    static size_t write_call_back(void *contents, size_t size, size_t nmemb, std::string *response);

    std::string generateUrl(const std::string &f, const std::string &t, const std::string &srcText);

    Json::Value connect(const std::string &f, const std::string &t, const std::string &srcText);

    friend class BaiduTranslator;

public:
    explicit TranslateConnection(BaiduUserInfo info);

    ~TranslateConnection() {
        delete info;
    };


};


#endif //BAIDUTRANSLATE_TRANSLATECONNECTION_H
