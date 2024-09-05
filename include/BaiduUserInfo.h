//
// Created by 2333 xiang on 2024/9/5.
//

#ifndef BAIDUTRANSLATE_BAIDUUSERINFO_H
#define BAIDUTRANSLATE_BAIDUUSERINFO_H

#include <string>
#include <sstream>

class TranslateConnection;

class BaiduUserInfo {
    std::string appid;
    std::string key;

    friend class TranslateConnection;

public:
    BaiduUserInfo(std::string &aid, std::string &auth_key);

    ~BaiduUserInfo() = default;
};


#endif //BAIDUTRANSLATE_BAIDUUSERINFO_H
