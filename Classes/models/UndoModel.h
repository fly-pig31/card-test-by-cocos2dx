#pragma once
#include "cocos2d.h"
#include "CardModel.h"

USING_NS_CC;

class UndoModel
{
public:
	void push(const CardModel& model) {
		_model.push_back(model);
	}
	CardModel undo() {
		auto model = _model.back();
		_model.pop_back();
		CCLOG("UndoModel::undo model id=%d,position=(%.1f,%.1f)", model.getId(), model.getPosition().x, model.getPosition().y);
		return model;
	}
	int size()const noexcept{
		return _model.size();
	}
	const CardModel& peek() const{
		return _model.back();
	}
private:
	//�洢�ɳ����Ŀ���ģ��
	std::deque<CardModel> _model;
};
//
//// ���˲�������
//enum UndoActionType {
//	UAT_NONE,
//	UAT_STACK_REPLACE, // �������滻
//	UAT_PLAYFIELD_MATCH // ������ƥ��
//};
//
//// �������˲���ģ��
//struct UndoStep {
//	UndoActionType type;
//	CardModel cardBefore; // ����ǰ�Ŀ���״̬
//	CardModel cardAfter;  // ������Ŀ���״̬
//	Vec2 originalPosition; // ԭʼλ�ã�����ƥ�������
//};
//
//// ���˼�¼ģ��
//struct UndoModel {
//	std::vector<UndoStep> steps;
//
//	void addStep(const UndoStep& step) {
//		steps.push_back(step);
//	}
//
//	bool hasSteps() const noexcept{
//		return !steps.empty();
//	}
//
//	UndoStep popLastStep() {
//		if (steps.empty()) return UndoStep{};
//		UndoStep last = steps.back();
//		steps.pop_back();
//		return last;
//	}
//};
//
