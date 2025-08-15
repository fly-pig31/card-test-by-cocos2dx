#pragma once
#include "cocos2d.h"
#include "models/GameModel.h"
#include "models/UndoModel.h"
#include "managers/UndoManager.h"
#include "services/GameModelFromLevelGenerator.h"
#include "configs/models/CardResConfig.h"
#include "configs/loaders/LevelConfigLoader.h"
#include "PlayFieldController.h"
#include "StackController.h"
/// <summary>
/// ��Ϸ���������࣬ͳ��������Ϸ���߼�����
/// Э����Ϸ�����������ƶѿ����������˹�������ģ��Ľ���
/// </summary>
class GameController :public cocos2d::Node {
private:
	PlayFieldController* _playFieldController = nullptr; // ��Ϸ��������ʵ��
	StackController* _stackController = nullptr; // �ƶѿ�����ʵ��

public:
	/// <summary>
	/// ������Ϸ��������ʵ��
	/// </summary>
	/// <returns>GameControllerʵ��ָ��</returns>
	static GameController* create();

	/// <summary>
	/// ��ʼָ���ؿ�����Ϸ
	/// </summary>
	/// <param name="levelId">�ؿ�ID�����ڼ��ض�Ӧ�ؿ�����</param>
	void startGame(int levelId);

protected:
	GameModel _gameModel; // ��Ϸ����ģ�ͣ��洢��ǰ��Ϸ������״̬�����ơ�λ�õȣ�

public:
	/// <summary>
	/// ��ȡ��ǰ��Ϸģ�ͣ�ֻ����
	/// </summary>
	/// <returns>��ǰ��Ϸģ�͵ĳ�������</returns>
	virtual inline GameModel getGameModel(void) const {
		return _gameModel;
	}

	/// <summary>
	/// ������Ϸģ�ͣ�������Ϸ״̬��
	/// </summary>
	/// <param name="var">�µ���Ϸģ��</param>
	virtual inline void setGameModel(GameModel var) {
		_gameModel = var;
	};

	/// <summary>
	/// ��Ϸ��ͼ��������Cocos2d-x�꣬�Զ�����get/set������
	/// ���ڻ�ȡ��������Ϸ����ͼ
	/// </summary>
	CC_SYNTHESIZE(GameView*, _gameView, GameView);

	/// <summary>
	/// ����ģ�ͷ�������Cocos2d-x�꣩
	/// ���ڻ�ȡ�����û���ģ�ͣ��洢�������ݣ�
	/// </summary>
	CC_SYNTHESIZE(UndoModel, _undoModel, UndoModel);

	/// <summary>
	/// ���˹�������������Cocos2d-x�꣬���ڴ����
	/// ���ڻ�ȡ�����û��˹�����
	/// </summary>
	CC_SYNTHESIZE_RETAIN(UndoManager*, _undoManager, UndoManager);

	/// <summary>
	/// ִ����һ�������Ļ���
	/// </summary>
	void undoOperation();
};