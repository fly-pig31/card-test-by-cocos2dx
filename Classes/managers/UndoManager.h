
#pragma once
#include "cocos2d.h"
#include "models/UndoModel.h"
#include "models/GameModel.h"
#include "views/GameView.h"

USING_NS_CC;
/// <summary>
/// ���˹������࣬�����¼���Ʋ�����ʷ��ִ�л��˲���
/// ͳһ������Ϸ�е����л����߼���Э������ģ����������Ľ���
/// </summary>
class UndoManager : public Node {
public:
	/// <summary>
	/// Cocos2d-x��׼�������������ڴ������˹�����ʵ��
	/// </summary>
	CREATE_FUNC(UndoManager);

	/// <summary>
	/// ִ����һ�������Ļ���
	/// </summary>
	/// <returns>���˺�Ŀ���ģ�ͣ��ָ�������ǰ��״̬��</returns>
	CardModel undo();

	/// <summary>
	/// ��¼���Ʋ���������ǰ����״̬���������ʷ��
	/// </summary>
	/// <param name="model">��Ҫ��¼�Ŀ���ģ�ͣ��������״̬��</param>
	void record(const CardModel& model);

	/// <summary>
	/// ����Ƿ����ִ�л��˲������Ƿ�����ʷ��¼��
	/// </summary>
	/// <returns>�пɻ��˵ļ�¼����true�����򷵻�false</returns>
	bool canUndo()const;

	/// <summary>
	/// �鿴���һ�μ�¼�Ŀ���״̬����ִ�л��ˣ�
	/// </summary>
	/// <returns>���һ�μ�¼�Ŀ���ģ�͵ĳ�������</returns>
	const CardModel& peek()const;

protected:
	UndoModel _undoModel; // ����ģ�ͣ��洢���Ʋ�������ʷ��¼
};