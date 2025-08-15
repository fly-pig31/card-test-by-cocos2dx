#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"
#include "configs/models/CardResConfig.h"

USING_NS_CC;
/// <summary>
/// 卡牌视图类，负责单个卡牌的显示和交互（点击、动画等）
/// 对应卡牌模型(CardModel)，展示卡牌的外观并处理用户输入
/// </summary>
class CardView : public Sprite {
public:
	/// <summary>
	/// 根据卡牌模型创建卡牌视图
	/// </summary>
	/// <param name="model">卡牌模型，包含卡牌的属性（面值、花色等）</param>
	/// <returns>卡牌视图(CardView)实例指针</returns>
	static CardView* create(const CardModel& model);

	/// <summary>
	/// 初始化卡牌视图（继承自Sprite的初始化方法）
	/// </summary>
	/// <param name="model">卡牌模型，用于初始化视图外观</param>
	/// <returns>初始化成功返回true，否则返回false</returns>
	virtual bool init(const CardModel& model);

	/// <summary>
	/// 设置卡牌点击回调函数
	/// </summary>
	/// <param name="callback">回调函数，参数为游戏区索引和卡牌ID</param>
	void setCallBack(std::function<void(int, int)>& callback) {
		this->_onClickCallback = callback;
	}

	/// <summary>
	/// 设置卡牌是否可点击
	/// </summary>
	/// <param name="clickable">true为可点击，false为不可点击</param>
	void setClickable(bool clickable) {
		_isClickable = clickable;
	}

	/// <summary>
	/// 移动卡牌到目标位置（带动画）
	/// </summary>
	/// <param name="position">目标位置（世界坐标系）</param>
	/// <param name="duration">动画持续时间（秒）</param>
	void moveToPosition(const Vec2& position, float duration);

	/// <summary>
	/// 卡牌抖动动画（用于提示不匹配等错误状态）
	/// </summary>
	void shake();

private:
	/// <summary>
	/// 创建卡牌正面的精灵（包含数字、花色等）
	/// </summary>
	/// <param name="model">卡牌模型，用于获取资源路径</param>
	void createFaceSprite(const CardModel& model);

	/// <summary>
	/// 创建卡牌背面的精灵（暂未实现）
	/// </summary>
	void createBackSprite();

	std::function<void(int, int)> _onClickCallback; // 点击回调函数，参数：游戏区索引、卡牌ID
	bool _isClickable = true; // 卡牌是否可点击的标志
	int _playFiledsIndex = -1; // 卡牌所在游戏区的索引（-1表示未在游戏区）
	int _tagId = -1; // 卡牌的唯一标识ID
};