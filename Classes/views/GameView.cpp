#include "GameView.h"
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void GameView::setup(const GameModel& model)
{
	//this->removeAllChildren();
	createUndoButton();
	this->setGlobalZOrder(-2);
	//_playFieldView = PlayFieldView::create();
	//_playFieldView->setUpWithCardModels(model);
	//_stackView = StackView::create();
	//_stackView->setUpWithCardModels(model);
	//addChild(_playFieldView);
	//addChild(_stackView);
}


void GameView::createUndoButton()
{
	const std::string btnText = "Undo";

	// 2. 创建按钮
	auto undoButton = ui::Button::create();
	undoButton->setLocalZOrder(INT_MAX);
	if (!undoButton) {
		CCLOG("ERROR: Failed to create undo button");
		return;
	}
		const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// 3. 配置按钮样式
	undoButton->setContentSize(Size(300, 100));
	undoButton->setTitleText(btnText);
	undoButton->setTitleFontSize(60);
	undoButton->setTitleColor(Color3B::WHITE);
	undoButton->setPosition(Vec2(visibleSize.width - 150, visibleSize.height/6));


	// 4. 设置按钮状态颜色
	undoButton->setColor(Color3B::RED); // 临时颜色
	undoButton->setPressedActionEnabled(true); // 启用按下状态动画

	// 5. 添加点击事件监听器
	undoButton->addClickEventListener([this](Ref* sender) {
		CCLOG("undoButton click");
		if (_undoCallback) {
			_undoCallback();
		}
		else {
			CCLOG("ERROR: undoCallback is null");

			// 视觉反馈
			auto btn = dynamic_cast<ui::Button*>(sender);
			if (btn) {
				btn->runAction(Sequence::create(
					TintTo::create(0.1f, Color3B(255, 100, 100)), // 浅红色
					TintTo::create(0.1f, Color3B::WHITE),
					nullptr
				));
			}
		}
		});
	// 添加按钮标签
	const auto label = Label::createWithTTF("Revoke the last operation", "fonts/Marker Felt.ttf", 28);
	label->setLocalZOrder(INT_MAX);
	label->setPosition(Vec2(undoButton->getPositionX(), undoButton->getPositionY() - 40));
	label->setColor(Color3B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	
	this->addChild(label, 10);
	// 6. 添加到视图
	this->addChild(undoButton, 1000);
}

bool GameView::init()
{
	if (!Layer::init()) {
		return false;
	}

}
