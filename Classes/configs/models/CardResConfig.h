#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"
#include <string>
USING_NS_CC;
/// <summary>
/// ������Դ�����࣬������ݿ���ģ�����ɶ�Ӧ����Դ·����ͼƬ�ȣ�
/// ͳһ�����Ƶ���Դ�����߼�
/// </summary>
class CardResConfig {
public:
	const std::string bigNumberPath;    // �������������ͼƬ·��
	const std::string smallNumberPath;  // ��������С����ͼƬ·��
	const std::string suitPath;         // ���ƻ�ɫͼƬ·��
	const char* cardGeneral = "res/card_general.png"; // ����ͨ�ñ���ͼ·��
	const Size cardSize;                // ���Ƴߴ磨Ĭ��120x180��

	/// <summary>
	/// ���캯�������ݿ���ģ�ͳ�ʼ����Դ·��
	/// </summary>
	/// <param name="model">����ģ�ͣ�������ֵ����ɫ����Ϣ</param>
	/// <param name="size">���Ƴߴ磬Ĭ��120x180</param>
	explicit CardResConfig(const CardModel& model, const Size& size = Size(120, 180))
		: cardSize(size),
		bigNumberPath(generateBigNumberPath(model)),
		smallNumberPath(generateSmallNumberPath(model)),
		suitPath(generateSuitPath(model))
	{}

private:
	/// <summary>
	/// ���ɴ�����ͼƬ·���������м�Ĵ����֣�
	/// </summary>
	/// <param name="model">����ģ�ͣ����ڻ�ȡ��ֵ�ͻ�ɫ</param>
	/// <returns>������ͼƬ������·��</returns>
	static std::string generateBigNumberPath(const CardModel& model) {
		return std::string("res/number/big_") + getColor(model) + "_" + CARD_FACES[model.getFace()] + ".png";
	}

	/// <summary>
	/// ����С����ͼƬ·�������ƽ����С���֣�
	/// </summary>
	/// <param name="model">����ģ�ͣ����ڻ�ȡ��ֵ�ͻ�ɫ</param>
	/// <returns>С����ͼƬ������·��</returns>
	static std::string generateSmallNumberPath(const CardModel& model) {
		return std::string("res/number/small_") + getColor(model) + "_" + CARD_FACES[model.getFace()] + ".png";
	}

	/// <summary>
	/// ���ɻ�ɫͼƬ·��
	/// </summary>
	/// <param name="model">����ģ�ͣ����ڻ�ȡ��ɫ</param>
	/// <returns>��ɫͼƬ������·��</returns>
	static std::string generateSuitPath(const CardModel& model) {
		return std::string("res/suits/") + CARD_SUITS[model.getSuit()] + ".png";
	}

	/// <summary>
	/// ���ݿ��ƻ�ɫ��ȡ��ɫ�ַ�������/�ڣ�
	/// </summary>
	/// <param name="model">����ģ�ͣ�������ɫ��Ϣ</param>
	/// <returns>��ɫ�ַ�����"red"��"black"��</returns>
	static const char* getColor(const CardModel& model) noexcept {
		// ����(HEARTS)�ͷ���(DIAMONDS)Ϊ��ɫ��÷��(CLUB)�ͺ���(SPADE)Ϊ��ɫ
		return (model.getSuit() == CST_HEARTS || model.getSuit() == CST_DIAMONDS) ? "red" : "black";
	}

	/// <summary>
	/// Ԥ���忨����ֵ�ַ�������CardFaceTypeö�ٶ�Ӧ��
	/// ����0��ӦA��1��Ӧ2��...��12��ӦK
	/// </summary>
	static constexpr const char* CARD_FACES[13] = {
		"A", "2", "3", "4", "5", "6", "7",
		"8", "9", "10", "J", "Q", "K"
	};

	/// <summary>
	/// Ԥ���忨�ƻ�ɫ�ַ�������CardSuitTypeö�ٶ�Ӧ��
	/// ����0��Ӧ÷����1��Ӧ���飬2��Ӧ���ң�3��Ӧ����
	/// </summary>
	static constexpr const char* CARD_SUITS[4] = {
		"club", "diamond", "heart", "spade"
	};
};