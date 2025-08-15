#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"
#include "configs/models/CardResConfig.h"

USING_NS_CC;
/// <summary>
/// ������ͼ�࣬���𵥸����Ƶ���ʾ�ͽ���������������ȣ�
/// ��Ӧ����ģ��(CardModel)��չʾ���Ƶ���۲������û�����
/// </summary>
class CardView : public Sprite {
public:
	/// <summary>
	/// ���ݿ���ģ�ʹ���������ͼ
	/// </summary>
	/// <param name="model">����ģ�ͣ��������Ƶ����ԣ���ֵ����ɫ�ȣ�</param>
	/// <returns>������ͼ(CardView)ʵ��ָ��</returns>
	static CardView* create(const CardModel& model);

	/// <summary>
	/// ��ʼ��������ͼ���̳���Sprite�ĳ�ʼ��������
	/// </summary>
	/// <param name="model">����ģ�ͣ����ڳ�ʼ����ͼ���</param>
	/// <returns>��ʼ���ɹ�����true�����򷵻�false</returns>
	virtual bool init(const CardModel& model);

	/// <summary>
	/// ���ÿ��Ƶ���ص�����
	/// </summary>
	/// <param name="callback">�ص�����������Ϊ��Ϸ�������Ϳ���ID</param>
	void setCallBack(std::function<void(int, int)>& callback) {
		this->_onClickCallback = callback;
	}

	/// <summary>
	/// ���ÿ����Ƿ�ɵ��
	/// </summary>
	/// <param name="clickable">trueΪ�ɵ����falseΪ���ɵ��</param>
	void setClickable(bool clickable) {
		_isClickable = clickable;
	}

	/// <summary>
	/// �ƶ����Ƶ�Ŀ��λ�ã���������
	/// </summary>
	/// <param name="position">Ŀ��λ�ã���������ϵ��</param>
	/// <param name="duration">��������ʱ�䣨�룩</param>
	void moveToPosition(const Vec2& position, float duration);

	/// <summary>
	/// ���ƶ���������������ʾ��ƥ��ȴ���״̬��
	/// </summary>
	void shake();

private:
	/// <summary>
	/// ������������ľ��飨�������֡���ɫ�ȣ�
	/// </summary>
	/// <param name="model">����ģ�ͣ����ڻ�ȡ��Դ·��</param>
	void createFaceSprite(const CardModel& model);

	/// <summary>
	/// �������Ʊ���ľ��飨��δʵ�֣�
	/// </summary>
	void createBackSprite();

	std::function<void(int, int)> _onClickCallback; // ����ص���������������Ϸ������������ID
	bool _isClickable = true; // �����Ƿ�ɵ���ı�־
	int _playFiledsIndex = -1; // ����������Ϸ����������-1��ʾδ����Ϸ����
	int _tagId = -1; // ���Ƶ�Ψһ��ʶID
};