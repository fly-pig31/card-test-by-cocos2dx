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
	/// �ƶ��������Ƶ�������
	/// </summary>
	/// <param name="plieIndex">�ƶ�����</param>
	void moveToStackTop(int plieIndex, int zOrder);
	/// <summary>
	/// ��ͼ���˲���
	/// </summary>
	/// <param name="plieIndex">�ƶ�����</param>
	/// <param name="model">����model</param>
	void moveUndo(const CardModel& model);
	/// <summary>
	/// ���Ų�ƥ��Ķ���
	/// </summary>
	/// <param name="tagId">����id</param>
	void unMatched(int tagId) const;
private:
	std::function<void(int, int)> _onClickCallback;
	std::vector<std::stack<int>> _pileCardTagIds;
private:
	/// <summary>
	/// ����ģ�������ͼ
	/// </summary>
	/// <param name="model">���Ƶ�����ģ��</param>
	void addCardView(const CardModel& model, int zOrder);
	/// <summary>
	/// Layer��߿����
	/// </summary>
	void drawBorder(const Size& visibleSize);
	CardView* getCardViewByTagId(int tagId) const;
private:
};
