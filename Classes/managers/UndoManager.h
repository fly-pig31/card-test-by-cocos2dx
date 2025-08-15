
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
    /// 执行回退操作
    /// </summary>
    /// <param name="gameModel">要操作的model</param>
    CardModel undo();
    /// <summary>
    /// 执行记录操作,记录可以回退的model
    /// </summary>
    /// <param name="model">可回退的CardModel</param>
    void record(const CardModel& model);
    /// <summary>
    /// 根据undoModel中是否有数据检测是否可以撤销
    /// </summary>
    /// <returns></returns>
    bool canUndo()const;
    /// <summary>
    /// 查看当前顶部卡牌
    /// </summary>
    /// <returns></returns>
    const CardModel& peek()const;
protected:
    UndoModel _undoModel;
    // 处理不同类型的回退操作
    //void undoStackReplace(const UndoStep& step);
    //void undoPlayfieldMatch(const UndoStep& step);
};