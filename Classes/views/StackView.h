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
	/// �ƶ���������ͼ
	/// </summary>
	/// <param name="zOrder">��Ⱦ�㼶</param>
	void moveToStackTop(int zOrder);
	/// <summary>
	/// ������������ͼ
	/// </summary>
	/// <param name="model">��Ҫ���˵Ŀ���model</param>
	void moveUndo(const CardModel& model);
private:
	std::function<void(int, int)> _onClickCallback;
	std::stack<int> _cardTagIds;
private:
	/// <summary>
	/// ����ģ�������ͼ
	/// </summary>
	/// <param name="model">���Ƶ�����ģ��</param>
	void addCardView(const CardModel& model);
	void drawBorder(const Size& visibleSize);
	int _stackNums = -1;
};

