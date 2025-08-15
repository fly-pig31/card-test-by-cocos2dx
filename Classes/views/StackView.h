#pragma once
#include <cocos2d.h>
#include "models/CardModel.h"
#include "models/GameModel.h"
#include "CardView.h"
#include "GameView.h"
USING_NS_CC;
class StackView :public cocos2d::Layer
{
public:
	CREATE_FUNC(StackView);
	bool init() override;
	void setUpWithCardModels(const GameModel& models);
	void setOnClickCallBack(std::function<void(int, int)> onClickCallback) {
		_onClickCallback = onClickCallback;
	}
	/// <summary>
	/// 移动手牌区视图
	/// </summary>
	/// <param name="zOrder">渲染层级</param>
	void moveToStackTop(int zOrder);
	/// <summary>
	/// 回退区手牌视图
	/// </summary>
	/// <param name="model">需要回退的卡牌model</param>
	void moveUndo(const CardModel& model);
private:
	std::function<void(int, int)> _onClickCallback;
	std::stack<int> _cardTagIds;
private:
	/// <summary>
	/// 根据模型添加视图
	/// </summary>
	/// <param name="model">卡牌的数据模型</param>
	void addCardView(const CardModel& model);
	void drawBorder(const Size& visibleSize);
	int _stackNums = -1;
};

