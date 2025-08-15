#include "CardView.h"
#include "configs/models/CardResConfig.h"
CardView* CardView::create(const CardModel& model)
{
	CardView* pRet = new(std::nothrow) CardView();
	if (pRet && pRet->init(model)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}

}

bool CardView::init(const CardModel& model)
{
	if (!Sprite::init()) {
		return false;
	}
	this->_position = model.getPosition();
	this->_tagId = model.getId();
	//this->cardTagId = model.getId();
	//创建卡牌正面
	createFaceSprite(model);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	_playFiledsIndex = model.getPlayIndex();
	listener->onTouchBegan = [this](Touch* touch, Event* event) -> bool {
		// 获取当前卡牌
		if (this->getChildrenCount() == 0) return false;
		auto cardSprite = this->getChildren().at(0);
		Vec2 touchLocation = this->convertTouchToNodeSpace(touch);

		if (cardSprite->getBoundingBox().containsPoint(touchLocation)) {
			CCLOG("CardView::onTouchBegan: Card clicked at (%.1f, %.1f)", touchLocation.x, touchLocation.y);
			this->runAction(Sequence::create(
				ScaleTo::create(0.1f, 1.0f),
				ScaleTo::create(0.1f, 0.8f),
				CallFunc::create([this]() {
					if (_isClickable && _onClickCallback) {
						_onClickCallback(_playFiledsIndex,_tagId);
					}}), nullptr));
			return true;
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	// 在卡牌上绘制锚点标记跟踪
	//auto dot = DrawNode::create();
	//dot->drawDot(Vec2::ZERO, 5, Color4F::RED);
	//this->addChild(dot, 100);
	// 在卡牌上绘制边框
	//auto debugDraw = DrawNode::create();
	//debugDraw->drawRect(Vec2::ZERO, this->getContentSize(), Color4F::GREEN);
	//this->addChild(debugDraw, INT_MAX);
	return true;
}

void CardView::moveToPosition(const Vec2& position, float duration)
{
	auto move = MoveTo::create(duration, position);
	this->runAction(move);
}

void CardView::shake()
{
	float duration = 0.5f, intensity = 5.0f;
	auto moveRight = MoveBy::create(0.05f, Vec2(intensity, 0));
	auto moveLeft = MoveBy::create(0.05f, Vec2(-intensity, 0));
	auto moveUp = MoveBy::create(0.05f, Vec2(0, intensity));
	auto moveDown = MoveBy::create(0.05f, Vec2(0, -intensity));

	// 组合动作
	auto shake = Sequence::create(
		moveRight, moveLeft,
		moveUp, moveDown,
		moveRight->reverse(), moveLeft->reverse(),
		nullptr
	);

	// 重复抖动
	auto repeat = Repeat::create(shake, duration / 0.3f);
	this->runAction(repeat);
}

void CardView::createFaceSprite(const CardModel& model)
{
	auto config = CardResConfig(model);
	// 创建底图
	auto faceSprite = Sprite::create(config.cardGeneral);
	if (!faceSprite) {
		CCLOG("Failed to create cardSprite");
	}
	auto smallNumSprite = Sprite::create(config.smallNumberPath);
	smallNumSprite->setAnchorPoint(Vec2(0, 1));
	smallNumSprite->setPosition(Vec2(10, faceSprite->getContentSize().height - 20));
	smallNumSprite->setScale(0.7f);
	faceSprite->addChild(smallNumSprite);

	// 花色
	auto smallSuitSprite = Sprite::create(config.suitPath);
	smallSuitSprite->setAnchorPoint(Vec2(1, 1));
	smallSuitSprite->setPosition(Vec2(faceSprite->getContentSize().width - 10, faceSprite->getContentSize().height - 20));
	smallSuitSprite->setScale(0.7f);
	faceSprite->addChild(smallSuitSprite);

	// 中间的数字
	auto bigNumSprite = Sprite::create(config.bigNumberPath);

	bigNumSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	bigNumSprite->setPosition(Vec2(faceSprite->getContentSize().width / 2, faceSprite->getContentSize().height / 2));
	bigNumSprite->setScale(0.9f);
	faceSprite->addChild(bigNumSprite);

	faceSprite->setPosition(this->convertToNodeSpace(model.getPosition()));
	this->addChild(faceSprite);

	this->setScale(0.8f);
}

void CardView::createBackSprite()
{
}
