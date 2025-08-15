//#pragma once
//#include "cocos2d.h"
//#include "CardModel.h"
//
//USING_NS_CC;
//
//// 游戏状态模型
//struct GameModel {
//    std::vector<CardModel> playfieldCards; // 桌面牌区的卡牌
//    std::vector<CardModel> stackCards;     // 手牌区的卡牌
//    
//    // 获取顶部卡牌（手牌区最后一张）
//    CardModel* getTopStackCard() {
//        if (stackCards.empty()) return nullptr;
//        return &stackCards.back();
//    }
//
//    // 根据位置查找卡牌
//    CardModel* findCardAtPosition(const Vec2& pos);
//};

#pragma once
#include "cocos2d.h"
#include "CardModel.h"
#include <stack>
#include <vector>
#define KLEN 50 
USING_NS_CC;
// 桌面牌区
struct PlayFieldPile {
	std::deque<CardModel> cards;
	//Vec2 basePosition;            // 牌堆基准位置
	//float cardOffsetY = 30.0f;   // 牌堆叠放时的Y轴偏移
	//CardModel* getTopCard() {
	//	return cards.empty() ? nullptr : &cards.top();
	//}
};

// 手牌区（牌堆+顶部牌）
struct StackArea {
	std::deque<CardModel> deck;      // 牌堆
	CardModel topCard;                // 顶部牌
	int topNums=0; //顶部堆叠的牌数量
	Vec2 deckPosition;                // 牌堆位置
	Vec2 topCardPosition;             // 顶部牌位置
};
class GameModel {
private:
	std::vector<PlayFieldPile> _playFieldPiles; // 桌面上的多个牌堆
	StackArea _stackArea;
public:
	/// <summary>
	/// 根据model的牌堆索引插入,需确保索引有效
	/// </summary>
	/// <param name="model"></param>
	void pushPlayFieldByIndex(const CardModel& model) {
		if (model.getPlayIndex() > _playFieldPiles.size() - 1) {
			throw std::runtime_error("Error: GameModel::pushPlayFieldByIndex,model playIndex invalid!");
		}
		_playFieldPiles.at(model.getPlayIndex()).cards.push_back(model);
	};
		/// <summary>
		/// 插入桌面牌堆，自动根据X轴距离分组
		/// </summary>
	void pushPlayField(const CardModel& model) {
		bool addedToExistingPile = false;

		// 遍历现有牌堆寻找合适分组
		for (auto& pile : _playFieldPiles) {
			if (!pile.cards.empty()) {
				const float lastCardX = pile.cards.back().getPosition().x;

				// 检查X轴距离是否在阈值内
				if (std::abs(model.getPosition().x - lastCardX) <= KLEN) {
					model.setPlayIndex(&pile - &_playFieldPiles[0]); // 设置牌堆索引
					pile.cards.push_back(model);
					addedToExistingPile = true;
					break;
				}
			}
		}

		// 如果没有找到合适牌堆，创建新牌堆
		if (!addedToExistingPile) {
			PlayFieldPile newPile;
			model.setPlayIndex(_playFieldPiles.size()); // 新牌堆索引
			newPile.cards.push_back(model);
			_playFieldPiles.push_back(newPile);
		}
	}
	/// <summary>
	/// 插入手牌区cardmodel
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
	/// 将当前手牌区的牌移动到手牌区顶部
	/// </summary>
	void stackMoveToStackTop() noexcept {
		this->_stackArea.topCard = _stackArea.deck.back();
		this->_stackArea.topCard.setPosition({ 400,200 });
		this->_stackArea.deck.pop_back();
	}
	/// <summary>
	/// 查找点击位置的卡牌
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	CardModel* findCardAtPosition(const Vec2& pos) {
		//// 1. 检查手牌区顶部牌
		//if (stackArea.topCard.isValid() &&
		//    stackArea.topCard.hitTest(pos)) {
		//    return &stackArea.topCard;
		//}

		//// 2. 检查桌面牌堆
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
	/// 将目标牌移动到手牌区顶部
	/// </summary>
	/// <param name="model">将被移动到手牌区顶部的模型</param>
	/// <returns>移动结果</returns>
	//bool moveToStackTop(CardModel& model) {
	//	model.setPosition({ 400,200 });
	//}
};