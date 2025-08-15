
#pragma once
#include "cocos2d.h"
#include "models/UndoModel.h"
#include "models/GameModel.h"
#include "views/GameView.h"

USING_NS_CC;

class UndoManager : public Node {
public:
    CREATE_FUNC(UndoManager);
    //bool init();
    /// <summary>
    /// ִ�л��˲���
    /// </summary>
    /// <param name="gameModel">Ҫ������model</param>
    CardModel undo();
    /// <summary>
    /// ִ�м�¼����,��¼���Ի��˵�model
    /// </summary>
    /// <param name="model">�ɻ��˵�CardModel</param>
    void record(const CardModel& model);
    /// <summary>
    /// ����undoModel���Ƿ������ݼ���Ƿ���Գ���
    /// </summary>
    /// <returns></returns>
    bool canUndo()const;
    /// <summary>
    /// �鿴��ǰ��������
    /// </summary>
    /// <returns></returns>
    const CardModel& peek()const;
protected:
    UndoModel _undoModel;
    // ����ͬ���͵Ļ��˲���
    //void undoStackReplace(const UndoStep& step);
    //void undoPlayfieldMatch(const UndoStep& step);
};