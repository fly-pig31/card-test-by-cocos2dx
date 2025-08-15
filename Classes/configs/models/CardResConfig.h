#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"
#include <string>
USING_NS_CC;
/// <summary>
/// 卡牌资源配置类，负责根据卡牌模型生成对应的资源路径（图片等）
/// 统一管理卡牌的资源加载逻辑
/// </summary>
class CardResConfig {
public:
	const std::string bigNumberPath;    // 卡牌正面大数字图片路径
	const std::string smallNumberPath;  // 卡牌正面小数字图片路径
	const std::string suitPath;         // 卡牌花色图片路径
	const char* cardGeneral = "res/card_general.png"; // 卡牌通用背景图路径
	const Size cardSize;                // 卡牌尺寸（默认120x180）

	/// <summary>
	/// 构造函数，根据卡牌模型初始化资源路径
	/// </summary>
	/// <param name="model">卡牌模型，包含面值、花色等信息</param>
	/// <param name="size">卡牌尺寸，默认120x180</param>
	explicit CardResConfig(const CardModel& model, const Size& size = Size(120, 180))
		: cardSize(size),
		bigNumberPath(generateBigNumberPath(model)),
		smallNumberPath(generateSmallNumberPath(model)),
		suitPath(generateSuitPath(model))
	{}

private:
	/// <summary>
	/// 生成大数字图片路径（卡牌中间的大数字）
	/// </summary>
	/// <param name="model">卡牌模型，用于获取面值和花色</param>
	/// <returns>大数字图片的完整路径</returns>
	static std::string generateBigNumberPath(const CardModel& model) {
		return std::string("res/number/big_") + getColor(model) + "_" + CARD_FACES[model.getFace()] + ".png";
	}

	/// <summary>
	/// 生成小数字图片路径（卡牌角落的小数字）
	/// </summary>
	/// <param name="model">卡牌模型，用于获取面值和花色</param>
	/// <returns>小数字图片的完整路径</returns>
	static std::string generateSmallNumberPath(const CardModel& model) {
		return std::string("res/number/small_") + getColor(model) + "_" + CARD_FACES[model.getFace()] + ".png";
	}

	/// <summary>
	/// 生成花色图片路径
	/// </summary>
	/// <param name="model">卡牌模型，用于获取花色</param>
	/// <returns>花色图片的完整路径</returns>
	static std::string generateSuitPath(const CardModel& model) {
		return std::string("res/suits/") + CARD_SUITS[model.getSuit()] + ".png";
	}

	/// <summary>
	/// 根据卡牌花色获取颜色字符串（红/黑）
	/// </summary>
	/// <param name="model">卡牌模型，包含花色信息</param>
	/// <returns>颜色字符串（"red"或"black"）</returns>
	static const char* getColor(const CardModel& model) noexcept {
		// 红桃(HEARTS)和方块(DIAMONDS)为红色，梅花(CLUB)和黑桃(SPADE)为黑色
		return (model.getSuit() == CST_HEARTS || model.getSuit() == CST_DIAMONDS) ? "red" : "black";
	}

	/// <summary>
	/// 预定义卡牌面值字符串（与CardFaceType枚举对应）
	/// 索引0对应A，1对应2，...，12对应K
	/// </summary>
	static constexpr const char* CARD_FACES[13] = {
		"A", "2", "3", "4", "5", "6", "7",
		"8", "9", "10", "J", "Q", "K"
	};

	/// <summary>
	/// 预定义卡牌花色字符串（与CardSuitType枚举对应）
	/// 索引0对应梅花，1对应方块，2对应红桃，3对应黑桃
	/// </summary>
	static constexpr const char* CARD_SUITS[4] = {
		"club", "diamond", "heart", "spade"
	};
};