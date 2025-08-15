#pragma once
#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/StackView.h"
#include "views/PlayFieldView.h"
#include <managers/UndoManager.h>
USING_NS_CC;
/// <summary>
/// ������������
/// </summary>
class StackController :public cocos2d::Node
{
public:
	CREATE_FUNC(StackController);
	void setUp(GameModel& model);
	void setUpView(const GameModel& model) {
		_stackView->setUpWithCardModels(model);
	}
	StackView* getView() const noexcept{
		return _stackView;
	}
	/// <summary>
	/// �ƶ����������Ƶ���������
	/// </summary>
	bool moveToStackTop(GameModel& model,int tagId);
	/// <summary>
	/// �����ƶ�����
	/// </summary>
	/// <returns></returns>
	bool moveUndo(const CardModel& model);
	void setUndoManager(UndoManager* undoManager) noexcept{
		_undoManager = undoManager;
	}
private:
	PlayFieldView* _playFieldView = nullptr;
	StackView* _stackView = nullptr;
	UndoManager* _undoManager;
};
