#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"
#include <string>
USING_NS_CC;

/// <summary>
/// 优化后的卡牌资源路径配置
/// </summary>
class CardResConfig {
public:


	const std::string bigNumberPath;    // 大数字纹理路径"res/
	const std::string smallNumberPath;  // 小数字纹理路径
	const std::string suitPath;         // 花色纹理路径
	const char* cardGeneral = "res/card_general.png";
	const Size cardSize;                // 卡牌尺寸

	// 构造函数 - 根据卡牌模型生成资源路径
	explicit CardResConfig(const CardModel& model, const Size& size = Size(120, 180))
		: cardSize(size),
		bigNumberPath(generateBigNumberPath(model)),
		smallNumberPath(generateSmallNumberPath(model)),
		suitPath(generateSuitPath(model))
	{}

private:
	// 生成大数字路径
	static std::string generateBigNumberPath(const CardModel& model) {
		return std::string("res/number/big_") + getColor(model) + "_" + CARD_FACES[model.getFace()] + ".png";
	}

	// 生成小数字路径
	static std::string generateSmallNumberPath(const CardModel& model) {
		return std::string("res/number/small_") + getColor(model) + "_" + CARD_FACES[model.getFace()] + ".png";
	}

	// 生成花色路径
	static std::string generateSuitPath(const CardModel& model) {
		return std::string("res/suits/") + CARD_SUITS[model.getSuit()] + ".png";
	}

	// 获取颜色字符串
	static const char* getColor(const CardModel& model) noexcept {
		return (model.getSuit() == CST_HEARTS || model.getSuit() == CST_DIAMONDS) ? "red" : "black";
	}
	// 预定义的卡牌面值和花色字符串
	static constexpr const char* CARD_FACES[13] = {
		"A", "2", "3", "4", "5", "6", "7",
		"8", "9", "10", "J", "Q", "K"
	};

	static constexpr const char* CARD_SUITS[4] = {
		"club", "diamond", "heart", "spade"
	};
};
