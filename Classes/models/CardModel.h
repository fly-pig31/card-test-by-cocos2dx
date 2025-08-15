#pragma once
#include "cocos2d.h"
USING_NS_CC;
// 卡牌花色类型
enum CardSuitType {
	CST_NONE = -1,
	CST_CLUBS,      // 梅花
	CST_DIAMONDS,   // 方块
	CST_HEARTS,     // 红桃
	CST_SPADES,     // 黑桃
	CST_NUM_CARD_SUIT_TYPES
};

// 卡牌面值类型
enum CardFaceType {
	CFT_NONE = -1,
	CFT_ACE,
	CFT_TWO,
	CFT_THREE,
	CFT_FOUR,
	CFT_FIVE,
	CFT_SIX,
	CFT_SEVEN,
	CFT_EIGHT,
	CFT_NINE,
	CFT_TEN,
	CFT_JACK,
	CFT_QUEEN,
	CFT_KING,
	CFT_NUM_CARD_FACE_TYPES
};

class CardModel {
private:
	int _id;					//标识id
	int mutable _playIndex=0;			//桌面区堆索引
	CardFaceType _face;
	CardSuitType _suit;
	Vec2 _position;         // 卡牌当前位置
	bool _isFaceUp = true; // 是否正面朝上
	bool _isInStack = false;// 是否在手牌区
	int _zOrder = 0;
	/**
 * 构造函数，用于创建卡牌模型对象
 * @param face 卡牌面值类型（如：A、2、3...K）
 * @param suit 卡牌花色类型（如：黑桃、红桃、梅花、方块）
 * @param position 卡牌在屏幕上的位置坐标
 * @param isFaceUp 是否正面朝上，默认为false（背面朝上）
 * @param isInStack 是否在牌堆中，默认为false
 * @param zOrder 卡牌的Z轴顺序（用于渲染层级），默认为0
 */
public:
	CardModel() = default;
	CardModel(int id, CardFaceType face, CardSuitType suit, Vec2 position, bool isFaceUp = false, bool isInStack = false, int zOrder = 0) :
		_id(id), _face(face), _suit(suit), _position(position), _isFaceUp(isFaceUp), _isInStack(isInStack), _zOrder(zOrder) {};
public:
	CardFaceType getFace()const {
		return _face;
	}
	CardSuitType getSuit() const {
		return _suit;
	}
	// 获取卡牌点数
	int getValue() const noexcept {
		return static_cast<int>(_face);
	}
	int getId() const noexcept {
		return _id;
	}
	Vec2 getPosition() const  {
		return _position;
	}
	void setPosition(const Vec2& position) noexcept {
		_position = position;
	}
	// 检查两张卡牌是否匹配
	bool isMatchable(const CardModel& other) const noexcept {
		return std::abs(getValue() - other.getValue()) == 1;
	}
	// 是否在手牌区
	bool isInStack() const noexcept {
		return _isInStack;
	}
	void setZOrder(int zOrder) noexcept {
		_zOrder = zOrder;
	}
	int getZOrder() const noexcept {
		return _zOrder;
	}
	void setPlayIndex(int index)const  noexcept {
		_playIndex = index;
	}
	int getPlayIndex() const noexcept {
		return _playIndex;
	}
};