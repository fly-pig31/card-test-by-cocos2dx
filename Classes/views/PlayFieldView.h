#pragma once
#include <cocos2d.h>
#include "models/CardModel.h"
#include "models/GameModel.h"
#include "CardView.h"
#include "GameView.h"
USING_NS_CC;
class PlayFieldView :public cocos2d::Layer
{
public:
	CREATE_FUNC(PlayFieldView);
	virtual bool init() override;
	//void setStackView(StackView*  view) { _stackView = view; };
	void setUpWithCardModels(const GameModel& models);
	void setOnClickCallBack(std::function<void(int, int)> onClickCallback) {
		_onClickCallback = onClickCallback;
	}
	/// <summary>
	/// 移动桌面区牌到手牌区
	/// </summary>
	/// <param name="plieIndex">牌堆索引</param>
	void moveToStackTop(int plieIndex, int zOrder);
	/// <summary>
	/// 视图回退操作
	/// </summary>
	/// <param name="plieIndex">牌堆索引</param>
	/// <param name="model">回退model</param>
	void moveUndo(const CardModel& model);
	/// <summary>
	/// 播放不匹配的动画
	/// </summary>
	/// <param name="tagId">卡牌id</param>
	void unMatched(int tagId) const;
private:
	std::function<void(int, int)> _onClickCallback;
	std::vector<std::stack<int>> _pileCardTagIds;
private:
	/// <summary>
	/// 根据模型添加视图
	/// </summary>
	/// <param name="model">卡牌的数据模型</param>
	void addCardView(const CardModel& model, int zOrder);
	/// <summary>
	/// Layer层边框绘制
	/// </summary>
	void drawBorder(const Size& visibleSize);
	CardView* getCardViewByTagId(int tagId) const;
private:
};
