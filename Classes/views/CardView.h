#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"
#include "configs/models/CardResConfig.h"

USING_NS_CC;
class GameView;
/// <summary>
/// 卡片视图类
/// 
/// 负责渲染卡牌视图
/// </summary>
class CardView : public Sprite {
public:
	/// <summary>
	/// 工厂创建方法创建view
	/// </summary>
	/// <param name="model">卡牌数据model</param>
	/// <returns>view指针</returns>
	static CardView* create(const CardModel& model);
	virtual bool init(const CardModel& model);
	void setCallBack(std::function<void(int, int)>& callback) {
		this->_onClickCallback = callback;
	}
	void setClickable(bool clickable) {
		_isClickable = clickable;
	}
	/// <summary>
	/// 将当前卡牌视图移动到目标位置
	/// </summary>
	/// <param name="position">目标位置</param>
	void moveToPosition(const Vec2& position, float duration);
	/// <summary>
	/// 卡牌抖动效果
	/// </summary>
	void shake();
	//void updateView(const CardModel& model);
	//void animateToPosition(const Vec2& position, float duration, const std::function<void()>& callback = nullptr);
private:

	void createFaceSprite(const CardModel& model);
	void createBackSprite();

	std::function<void(int,int)> _onClickCallback;            // 点击回调
	//std::function<void()> _onUndoCallback;			   //撤销回调
	bool _isClickable = true;							// 是否可点击
	int _playFiledsIndex = -1;								//所在牌堆索引(针对桌面区)
	int _tagId = -1;
};