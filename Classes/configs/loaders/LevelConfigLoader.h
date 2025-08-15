#pragma once
#include "configs/models/LevelConfig.h"
#include "utils/JsonParser.h"
#include <iostream>
#ifdef _WIN32
#include <direct.h>
#define GETCWD _getcwd
#else
#include <unistd.h>
#define GETCWD getcwd
#endif
namespace cocos2d {
	class LevelConfigLoader {
	public:
		static LevelConfig loadLevelConfig(int levelId) {
			LevelConfig config;
			std::string levelConfigJsonPath;
			switch (levelId)
			{
			case 1:
				levelConfigJsonPath = "res/level_1_config.json";
				break;
			default:
				break;
			}
			if (!FileUtils::getInstance()->isFileExist(levelConfigJsonPath)) {
				CCLOG("错误：文件不存在！");
				// 打印搜索路径
				auto searchPaths = FileUtils::getInstance()->getSearchPaths();
				CCLOG("当前资源路径:");
				for (const auto& path : searchPaths) {
					CCLOG(" - %s", path.c_str());
				}

				// 打印工作目录
				char buffer[1024];
				if (GETCWD(buffer, sizeof(buffer))) {
					CCLOG("当前目录: %s", buffer);
				}
			}
			auto json = JsonParser::parseJsonFile(levelConfigJsonPath);
			// 桌面牌区
			const auto& playfield = json["Playfield"];
			for (const auto& card : playfield.GetArray()) {
				CardConfig cardConfig;

				cardConfig.suit = static_cast<CardSuitType>(card["CardSuit"].GetInt());
				cardConfig.face = static_cast<CardFaceType>(card["CardFace"].GetInt());
		
				const auto& pos = card["Position"];
				cardConfig.position = Vec2(pos["x"].GetFloat(), pos["y"].GetFloat());
				config.playfield.push_back(cardConfig);
			}
			// 手牌区
			const auto& stack = json["Stack"];
			for (const auto& card : stack.GetArray()) {
				CardConfig cardConfig;
				cardConfig.suit = static_cast<CardSuitType>(card["CardSuit"].GetInt());
				cardConfig.face = static_cast<CardFaceType>(card["CardFace"].GetInt());
		
				const auto& pos = card["Position"];
				cardConfig.position = Vec2(pos["x"].GetFloat(), pos["y"].GetFloat());
				config.stack.push_back(cardConfig);
			}

			return config;
		}
	};
};