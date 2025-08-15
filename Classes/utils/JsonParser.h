#pragma once
#include "cocos2d.h"
#include "json/document.h"

class JsonParser {
public:
    
    static rapidjson::Document parseJsonFile(const std::string& filePath) {
        if (filePath.empty()) {
            throw std::runtime_error("Error in JsonParser::parseJsonFile:filePath:"+filePath+" is empty.");
        }
        rapidjson::Document doc;
        doc.Parse(cocos2d::FileUtils::getInstance()->getStringFromFile(filePath).c_str());
        return doc;
    }
};