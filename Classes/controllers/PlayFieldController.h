#pragma once
#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/PlayFieldView.h"
#include "views/StackView.h"
#include "managers/UndoManager.h"
/// <summary>
/// ��Ϸ���������࣬���������Ϸ�����Ƶ��߼��������ƶ������˵ȣ�
/// Э����Ϸ����ͼ(PlayFieldView)����Ϸģ��(GameModel)�Ľ���
/// </summary>
class PlayFieldController :public cocos2d::Node {
public:
	/// <summary>
	/// Cocos2d-x��׼�������������ڴ���������ʵ��
	/// </summary>
	CREATE_FUNC(PlayFieldController);

	/// <summary>
	/// ����Ϸ���Ŀ����ƶ����ƶѶ���
	/// </summary>
	/// <param name="model">��Ϸģ�ͣ��洢��ǰ��Ϸ״̬</param>
	/// <param name="playFiledIndex">��Ϸ�����ƶѵ�����</param>
	/// <param name="tagId">Ҫ�ƶ��Ŀ���ID</param>
	/// <returns>�ƶ��ɹ�����true��ʧ�ܷ���false���翨�Ʋ�ƥ�䣩</returns>
	bool moveToStackTop(GameModel& model, int playFiledIndex, int tagId);
	/// <summary>
	/// ִ����Ϸ�����ƵĻ��˲����������ƻָ���֮ǰ��״̬/λ�ã�
	/// </summary>
	/// <param name="model">��Ҫ���˵Ŀ���ģ��</param>
	/// <returns>���˳ɹ�����true�����򷵻�false</returns>
	bool moveUndo(const CardModel& model);

	/// <summary>
	/// ���û��˹����������ڼ�¼��ִ�л��˲���
	/// </summary>
	/// <param name="undoManager">���˹�����ʵ��</param>
	void setUndoManager(UndoManager* undoManager) noexcept {
		_undoManager = undoManager;
	}
	/// <summary>
	/// ��ʼ����Ϸ����ͼ���������
	/// </summary>
	/// <param name="model">��Ϸ����ģ�ͣ����ڳ�ʼ����ͼ</param>
	void setUp(GameModel& model);
	/// <summary>
	/// ������Ϸģ�͸�����Ϸ����ͼ
	/// </summary>
	/// <param name="model">��ǰ��Ϸģ�ͣ��������µĿ���״̬</param>
	void setUpView(const GameModel& model) {
		_playFieldView->setUpWithCardModels(model);
	};
	/// <summary>
	/// ��ȡ��Ϸ����ͼʵ��
	/// </summary>
	/// <returns>��Ϸ����ͼ(PlayFieldView)ָ��</returns>
	PlayFieldView* getView() const noexcept {
		return _playFieldView;
	}
private:
	PlayFieldView* _playFieldView = nullptr; // ��Ϸ����ͼʵ������������ʾ
	StackView* _stackView = nullptr; // �ƶ���ͼʵ�������ڽ���
	UndoManager* _undoManager; // ���˹����������ڼ�¼������ʷ
};