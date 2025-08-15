//#pragma once
//#include "cocos2d.h"
//#include "CardModel.h"
//
//USING_NS_CC;
//
//// ��Ϸ״̬ģ��
//struct GameModel {
//    std::vector<CardModel> playfieldCards; // ���������Ŀ���
//    std::vector<CardModel> stackCards;     // �������Ŀ���
//    
//    // ��ȡ�������ƣ����������һ�ţ�
//    CardModel* getTopStackCard() {
//        if (stackCards.empty()) return nullptr;
//        return &stackCards.back();
//    }
//
//    // ����λ�ò��ҿ���
//    CardModel* findCardAtPosition(const Vec2& pos);
//};

#pragma once
#include "cocos2d.h"
#include "CardModel.h"
#include <stack>
#include <vector>
#define KLEN 50 
USING_NS_CC;
// ��������
struct PlayFieldPile {
	std::deque<CardModel> cards;
	//Vec2 basePosition;            // �ƶѻ�׼λ��
	//float cardOffsetY = 30.0f;   // �ƶѵ���ʱ��Y��ƫ��
	//CardModel* getTopCard() {
	//	return cards.empty() ? nullptr : &cards.top();
	//}
};

// ���������ƶ�+�����ƣ�
struct StackArea {
	std::deque<CardModel> deck;      // �ƶ�
	CardModel topCard;                // ������
	int topNums=0; //�����ѵ���������
	Vec2 deckPosition;                // �ƶ�λ��
	Vec2 topCardPosition;             // ������λ��
};
class GameModel {
private:
	std::vector<PlayFieldPile> _playFieldPiles; // �����ϵĶ���ƶ�
	StackArea _stackArea;
public:
	/// <summary>
	/// ����model���ƶ���������,��ȷ��������Ч
	/// </summary>
	/// <param name="model"></param>
	void pushPlayFieldByIndex(const CardModel& model) {
		if (model.getPlayIndex() > _playFieldPiles.size() - 1) {
			throw std::runtime_error("Error: GameModel::pushPlayFieldByIndex,model playIndex invalid!");
		}
		_playFieldPiles.at(model.getPlayIndex()).cards.push_back(model);
	};
		/// <summary>
		/// ���������ƶѣ��Զ�����X��������
		/// </summary>
	void pushPlayField(const CardModel& model) {
		bool addedToExistingPile = false;

		// ���������ƶ�Ѱ�Һ��ʷ���
		for (auto& pile : _playFieldPiles) {
			if (!pile.cards.empty()) {
				const float lastCardX = pile.cards.back().getPosition().x;

				// ���X������Ƿ�����ֵ��
				if (std::abs(model.getPosition().x - lastCardX) <= KLEN) {
					model.setPlayIndex(&pile - &_playFieldPiles[0]); // �����ƶ�����
					pile.cards.push_back(model);
					addedToExistingPile = true;
					break;
				}
			}
		}

		// ���û���ҵ������ƶѣ��������ƶ�
		if (!addedToExistingPile) {
			PlayFieldPile newPile;
			model.setPlayIndex(_playFieldPiles.size()); // ���ƶ�����
			newPile.cards.push_back(model);
			_playFieldPiles.push_back(newPile);
		}
	}
	/// <summary>
	/// ����������cardmodel
	/// </summary>
	void pushStackArea(const CardModel& model) {
		_stackArea.deck.push_back(model);
	}
	std::vector<PlayFieldPile> getPlayFieldPile() const {
		return _playFieldPiles;
	}
	std::vector<PlayFieldPile>& getPlayFieldPile() {
		return _playFieldPiles;
	}
	inline StackArea getStackArea() const {
		return _stackArea;
	}
	inline StackArea& getStackArea() {
		return _stackArea;
	}
	/// <summary>
	/// ����ǰ�����������ƶ�������������
	/// </summary>
	void stackMoveToStackTop() noexcept {
		this->_stackArea.topCard = _stackArea.deck.back();
		this->_stackArea.topCard.setPosition({ 400,200 });
		this->_stackArea.deck.pop_back();
	}
	/// <summary>
	/// ���ҵ��λ�õĿ���
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	CardModel* findCardAtPosition(const Vec2& pos) {
		//// 1. ���������������
		//if (stackArea.topCard.isValid() &&
		//    stackArea.topCard.hitTest(pos)) {
		//    return &stackArea.topCard;
		//}

		//// 2. ��������ƶ�
		//for (auto& pile : playFieldPiles) {
		//    if (auto topCard = pile.getTopCard()) {
		//        if (topCard->hitTest(pos)) {
		//            return topCard;
		//        }
		//    }
		//}

		return nullptr;
	}
	/// <summary>
	/// ��Ŀ�����ƶ�������������
	/// </summary>
	/// <param name="model">�����ƶ���������������ģ��</param>
	/// <returns>�ƶ����</returns>
	//bool moveToStackTop(CardModel& model) {
	//	model.setPosition({ 400,200 });
	//}
};