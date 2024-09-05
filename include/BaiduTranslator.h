//
// Created by 2333 xiang on 2024/9/5.
//

#ifndef BAIDUTRANSLATE_BAIDUTRANSLATOR_H
#define BAIDUTRANSLATE_BAIDUTRANSLATOR_H

#include "TranslateConnection.h"
#include "BaiduUserInfo.h"
#include <string>
#include <unordered_map>
#include <json/json.h>

class BaiduTranslator {
    BaiduUserInfo *info;
public:
    static std::unordered_map<std::string, std::string> languageMap;
    static std::unordered_map<std::string, std::string> reverseMap;

    BaiduTranslator(std::string aid, std::string key);

    ~BaiduTranslator() {
        delete info;
    };

    std::string translate(const std::string &from, const std::string &to, const std::string &src);

};


#endif //BAIDUTRANSLATE_BAIDUTRANSLATOR_H
