#include "StackView.h"

bool StackView::init()
{
	if (!Layer::init())
	{
		return false;
	}
}

void StackView::setUpWithCardModels(const GameModel& models)
{
	//清除所有子元素
	this->removeAllChildren();
	this->_stackNums = models.getStackArea().deck.size();
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();
	const auto layer = LayerColor::create(
		Color4B(128, 0, 128, 255), // 紫色 (RGB: 128,0,128)
		visibleSize.width,
		visibleSize.height / 3
	);
	this->addChild(layer, INT_MIN);
	this->setPosition(origin);

	//this->drawBorder(visibleSize);
	//复制deck
	auto deck = models.getStackArea().deck;
	for (auto& model : deck) {
		addCardView(model);
	}
}

void StackView::addCardView(const CardModel& model)
{
	auto cardView = CardView::create(model);
	_cardTagIds.push(model.getId());
	if (cardView) {
		//设置点击回调
		cardView->setCallBack(_onClickCallback);
		this->getParent()->addChild(cardView, model.getZOrder(), model.getId());
	}
	else
	{
		CCLOG("PlayFieldView::addCardView Error: addCardView Failed");
	}
}

void StackView::moveToStackTop(int zOrder)
{
	if (_cardTagIds.empty()) {
		CCLOG("Stack empty");
		return;
	}
	const auto card = dynamic_cast<CardView*>(this->getParent()->getChildByTag(_cardTagIds.top()));
	//card->setGlobalZOrder(zOrder);
	card->setLocalZOrder(zOrder);
	const auto originPos = card->getPosition();
	const Vec2 targetPos = this->getParent()->convertToNodeSpace(Vec2(700, 350));
	// 定义回调函数
	auto callback = CallFunc::create([=]() {
		CCLOG("Moved CardView: (%.1f, %.1f) -> (%.1f, %.1f),zOrder:%d,globalZOrder:%d",
		originPos.x, originPos.y, card->getPosition().x, card->getPosition().y, card->getZOrder(), card->getGlobalZOrder());
		});


	// 创建动作序列：移动 + 回调
	card->runAction(Sequence::create(
		MoveTo::create(0.3f, targetPos),
		callback, nullptr));
	card->setClickable(false);
	_cardTagIds.pop();
}
void StackView::moveUndo(const CardModel& model)
{
	_cardTagIds.push(model.getId());

	const auto card = dynamic_cast<CardView*>(this->getParent()->getChildByTag(_cardTagIds.top()));
	card->setClickable(true);
	const auto originPos = card->getPosition();
	const Vec2 targetPos = this->getParent()->convertToNodeSpace(model.getPosition());
	// 定义回调函数
	auto callback = CallFunc::create([=]() {
		CCLOG("undo Moved CardView: (%.1f, %.1f) -> (%.1f, %.1f)",
		originPos.x, originPos.y, card->getPosition().x, card->getPosition().y);

		});

	card->setLocalZOrder(_cardTagIds.size());
	// 创建动作序列：移动 + 回调
	card->runAction(Sequence::create(
		MoveTo::create(0.3f, targetPos),
		callback, nullptr));
}
void StackView::drawBorder(const Size& visibleSize)
{
	//创建DrawNode绘制边框
	auto drawNode = DrawNode::create();
	float borderWidth = 5.0f; // 边框宽度
	Color4F borderColor = Color4F::RED; // 边框颜色

	//绘制矩形边框（考虑Layer的锚点）
	Vec2 vertices[4] = {
		Vec2(0, 0),
		Vec2(visibleSize.width, 0),
		Vec2(visibleSize.width, visibleSize.height),
		Vec2(0, visibleSize.height)
	};
	drawNode->drawPoly(vertices, 4, true, borderColor);

	//添加到Layer
	this->addChild(drawNode, INT_MAX); // 确保边框在最上层
}




