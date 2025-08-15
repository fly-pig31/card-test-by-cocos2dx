#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"
#include <string>
USING_NS_CC;

/// <summary>
/// �Ż���Ŀ�����Դ·������
/// </summary>
class CardResConfig {
public:


	const std::string bigNumberPath;    // ����������·��"res/
	const std::string smallNumberPath;  // С��������·��
	const std::string suitPath;         // ��ɫ����·��
	const char* cardGeneral = "res/card_general.png";
	const Size cardSize;                // ���Ƴߴ�

	// ���캯�� - ���ݿ���ģ��������Դ·��
	explicit CardResConfig(const CardModel& model, const Size& size = Size(120, 180))
		: cardSize(size),
		bigNumberPath(generateBigNumberPath(model)),
		smallNumberPath(generateSmallNumberPath(model)),
		suitPath(generateSuitPath(model))
	{}

private:
	// ���ɴ�����·��
	static std::string generateBigNumberPath(const CardModel& model) {
		return std::string("res/number/big_") + getColor(model) + "_" + CARD_FACES[model.getFace()] + ".png";
	}

	// ����С����·��
	static std::string generateSmallNumberPath(const CardModel& model) {
		return std::string("res/number/small_") + getColor(model) + "_" + CARD_FACES[model.getFace()] + ".png";
	}

	// ���ɻ�ɫ·��
	static std::string generateSuitPath(const CardModel& model) {
		return std::string("res/suits/") + CARD_SUITS[model.getSuit()] + ".png";
	}

	// ��ȡ��ɫ�ַ���
	static const char* getColor(const CardModel& model) noexcept {
		return (model.getSuit() == CST_HEARTS || model.getSuit() == CST_DIAMONDS) ? "red" : "black";
	}
	// Ԥ����Ŀ�����ֵ�ͻ�ɫ�ַ���
	static constexpr const char* CARD_FACES[13] = {
		"A", "2", "3", "4", "5", "6", "7",
		"8", "9", "10", "J", "Q", "K"
	};

	static constexpr const char* CARD_SUITS[4] = {
		"club", "diamond", "heart", "spade"
	};
};
