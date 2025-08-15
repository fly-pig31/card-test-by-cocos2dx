#pragma once
#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/StackView.h"
#include "views/PlayFieldView.h"
#include <managers/UndoManager.h>
USING_NS_CC;
/// <summary>
/// �ƶѿ������࣬��������ƶ�����Ŀ����߼��������ƶ������˵ȣ�
/// Э���ƶ���ͼ(StackView)����Ϸģ��(GameModel)�Ľ���
/// </summary>
class StackController :public cocos2d::Node
{
public:
	/// <summary>
	/// Cocos2d-x��׼�������������ڴ����ƶѿ�����ʵ��
	/// </summary>
	CREATE_FUNC(StackController);

	/// <summary>
	/// ��ʼ���ƶѿ���������ͼ
	/// </summary>
	/// <param name="model">��Ϸ����ģ�ͣ����ڳ�ʼ����ͼ</param>
	void setUp(GameModel& model);

	/// <summary>
	/// ������Ϸģ�͸����ƶ���ͼ
	/// </summary>
	/// <param name="model">��ǰ��Ϸģ�ͣ��������µ��ƶ�״̬</param>
	void setUpView(const GameModel& model) {
		_stackView->setUpWithCardModels(model);
	}

	/// <summary>
	/// ��ȡ�ƶ���ͼʵ��
	/// </summary>
	/// <returns>�ƶ���ͼ(StackView)ָ��</returns>
	StackView* getView() const noexcept {
		return _stackView;
	}

	/// <summary>
	/// ���ƶ��еĿ����ƶ����ƶѶ���
	/// </summary>
	/// <param name="model">��Ϸģ�ͣ��洢��ǰ��Ϸ״̬</param>
	/// <param name="tagId">Ҫ�ƶ��Ŀ���ID</param>
	/// <returns>�ƶ��ɹ�����true��ʧ�ܷ���false</returns>
	bool moveToStackTop(GameModel& model, int tagId);

	/// <summary>
	/// ִ���ƶѿ��ƵĻ��˲����������ƻָ���֮ǰ��״̬/λ�ã�
	/// </summary>
	/// <returns>���˳ɹ�����true�����򷵻�false</returns>
	bool moveUndo(const CardModel& model);

	/// <summary>
	/// ���û��˹����������ڼ�¼��ִ�л��˲���
	/// </summary>
	/// <param name="undoManager">���˹�����ʵ��</param>
	void setUndoManager(UndoManager* undoManager) noexcept {
		_undoManager = undoManager;
	}

private:
	PlayFieldView* _playFieldView = nullptr; // ��Ϸ����ͼ�����ڿ����򽻻���
	StackView* _stackView = nullptr; // �ƶ���ͼʵ���������ƶ���ʾ
	UndoManager* _undoManager; // ���˹����������ڼ�¼������ʷ
};