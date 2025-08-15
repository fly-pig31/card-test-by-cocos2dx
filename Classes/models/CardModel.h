#pragma once
#include "cocos2d.h"
USING_NS_CC;
// ���ƻ�ɫ����
enum CardSuitType {
	CST_NONE = -1,
	CST_CLUBS,      // ÷��
	CST_DIAMONDS,   // ����
	CST_HEARTS,     // ����
	CST_SPADES,     // ����
	CST_NUM_CARD_SUIT_TYPES
};

// ������ֵ����
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
	int _id;					//��ʶid
	int mutable _playIndex=0;			//������������
	CardFaceType _face;
	CardSuitType _suit;
	Vec2 _position;         // ���Ƶ�ǰλ��
	bool _isFaceUp = true; // �Ƿ����泯��
	bool _isInStack = false;// �Ƿ���������
	int _zOrder = 0;
	/**
 * ���캯�������ڴ�������ģ�Ͷ���
 * @param face ������ֵ���ͣ��磺A��2��3...K��
 * @param suit ���ƻ�ɫ���ͣ��磺���ҡ����ҡ�÷�������飩
 * @param position ��������Ļ�ϵ�λ������
 * @param isFaceUp �Ƿ����泯�ϣ�Ĭ��Ϊfalse�����泯�ϣ�
 * @param isInStack �Ƿ����ƶ��У�Ĭ��Ϊfalse
 * @param zOrder ���Ƶ�Z��˳��������Ⱦ�㼶����Ĭ��Ϊ0
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
	// ��ȡ���Ƶ���
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
	// ������ſ����Ƿ�ƥ��
	bool isMatchable(const CardModel& other) const noexcept {
		return std::abs(getValue() - other.getValue()) == 1;
	}
	// �Ƿ���������
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