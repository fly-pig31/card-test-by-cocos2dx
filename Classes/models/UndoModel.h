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
	//存储可撤销的卡牌模型
	std::deque<CardModel> _model;
};
//
//// 回退操作类型
//enum UndoActionType {
//	UAT_NONE,
//	UAT_STACK_REPLACE, // 手牌区替换
//	UAT_PLAYFIELD_MATCH // 桌面牌匹配
//};
//
//// 单步回退操作模型
//struct UndoStep {
//	UndoActionType type;
//	CardModel cardBefore; // 操作前的卡牌状态
//	CardModel cardAfter;  // 操作后的卡牌状态
//	Vec2 originalPosition; // 原始位置（用于匹配操作）
//};
//
//// 回退记录模型
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
