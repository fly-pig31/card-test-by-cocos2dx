#pragma once
#include "cocos2d.h"
#include "CardModel.h"

USING_NS_CC;
#pragma once
#include "cocos2d.h"
#include "CardModel.h"

USING_NS_CC;

/// <summary>
/// ����ģ���࣬����洢���Ʋ�������ʷ��¼
/// �ṩ��Ӽ�¼����ȡ�����¼��ɾ����¼�Ȼ�������
/// </summary>
class UndoModel
{
public:
	/// <summary>
	/// ���һ�����Ʋ�����¼��������״̬������ʷ��
	/// </summary>
	/// <param name="model">��Ҫ��¼�Ŀ���ģ��</param>
	void push(const CardModel& model) {
		_model.push_back(model);
	}

	/// <summary>
	/// �Ƴ����������һ�εļ�¼�����ڻ��ˣ�
	/// </summary>
	/// <returns>���һ�μ�¼�Ŀ���ģ��</returns>
	CardModel undo() {
		auto model = _model.back();
		_model.pop_back();
		CCLOG("UndoModel::undo model id=%d,position=(%.1f,%.1f)", model.getId(), model.getPosition().x, model.getPosition().y);
		return model;
	}

	/// <summary>
	/// ��ȡ��ǰ��¼������
	/// </summary>
	/// <returns>��¼����</returns>
	int size()const noexcept {
		return _model.size();
	}

	/// <summary>
	/// �鿴���һ�μ�¼����ɾ����
	/// </summary>
	/// <returns>���һ�μ�¼�Ŀ���ģ�͵ĳ�������</returns>
	const CardModel& peek() const {
		return _model.back();
	}

private:
	// �洢���Ʋ�����ʷ��˫�˶��У�֧�ָ�Ч��β�������ɾ����
	std::deque<CardModel> _model;
};