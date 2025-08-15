#pragma once
#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/PlayFieldView.h"
#include "views/StackView.h"
#include "managers/UndoManager.h"
USING_NS_CC;
/// <summary>
/// ������������
/// </summary>
class PlayFieldController :public cocos2d::Node {
public:
	CREATE_FUNC(PlayFieldController);
	/// <summary>
	/// �ƶ����������Ƶ���������
	/// </summary>
	bool moveToStackTop(GameModel& model, int playFiledIndex,int tagId);
	/// <summary>
	/// �����ƶ�����
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	bool moveUndo(const CardModel& model);
	/// <summary>
	/// ���û��˹�����
	/// </summary>
	/// <param name="undoManager"></param>
	void setUndoManager(UndoManager* undoManager) noexcept {
		_undoManager = undoManager;
	}
	/// <summary>
	/// ��ʼ����ͼ�Ϳ�����
	/// </summary>
	/// <param name="model">�ؿ���Ϸ����ģ��</param>
	void setUp(GameModel& model);
	void setUpView(const GameModel& model) {
		_playFieldView->setUpWithCardModels(model);
	};
	PlayFieldView* getView() const noexcept {
		return _playFieldView;
	}
private:
	PlayFieldView* _playFieldView = nullptr;
	StackView* _stackView = nullptr;
	UndoManager* _undoManager;
};

