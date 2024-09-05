//
// Created by 2333 xiang on 2024/9/5.
//

#ifndef BAIDUTRANSLATE_CODEUTIL_H
#define BAIDUTRANSLATE_CODEUTIL_H

#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/md5.h>
#include <curl/curl.h>


class CodeUtil {
public:
    static std::string generateSignature(const std::string &appid, const std::string &q, const std::string &salt,
                                         const std::string &secretKey);

    static std::string urlEncode(const std::string &value);
};


#endif //BAIDUTRANSLATE_CODEUTIL_H
