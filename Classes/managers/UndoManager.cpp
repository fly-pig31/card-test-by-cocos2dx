#include "UndoManager.h"

CardModel UndoManager::undo()
{

	return _undoModel.undo();
}
void UndoManager::record(const CardModel& model)
{
	CCLOG("UndoManager::record model id=%d,position=(%.1f,%.1f)", model.getId(), model.getPosition().x, model.getPosition().y);
	_undoModel.push(model);
}

const CardModel& UndoManager::peek() const
{
	return _undoModel.peek();
}

bool UndoManager::canUndo() const
{
	return _undoModel.size() > 1;
}
