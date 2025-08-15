#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"
#include "configs/models/CardResConfig.h"

USING_NS_CC;
class GameView;
/// <summary>
/// ��Ƭ��ͼ��
/// 
/// ������Ⱦ������ͼ
/// </summary>
class CardView : public Sprite {
public:
	/// <summary>
	/// ����������������view
	/// </summary>
	/// <param name="model">��������model</param>
	/// <returns>viewָ��</returns>
	static CardView* create(const CardModel& model);
	virtual bool init(const CardModel& model);
	void setCallBack(std::function<void(int, int)>& callback) {
		this->_onClickCallback = callback;
	}
	void setClickable(bool clickable) {
		_isClickable = clickable;
	}
	/// <summary>
	/// ����ǰ������ͼ�ƶ���Ŀ��λ��
	/// </summary>
	/// <param name="position">Ŀ��λ��</param>
	void moveToPosition(const Vec2& position, float duration);
	/// <summary>
	/// ���ƶ���Ч��
	/// </summary>
	void shake();
	//void updateView(const CardModel& model);
	//void animateToPosition(const Vec2& position, float duration, const std::function<void()>& callback = nullptr);
private:

	void createFaceSprite(const CardModel& model);
	void createBackSprite();

	std::function<void(int,int)> _onClickCallback;            // ����ص�
	//std::function<void()> _onUndoCallback;			   //�����ص�
	bool _isClickable = true;							// �Ƿ�ɵ��
	int _playFiledsIndex = -1;								//�����ƶ�����(���������)
	int _tagId = -1;
};