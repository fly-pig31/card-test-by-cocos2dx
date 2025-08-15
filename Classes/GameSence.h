#pragma once
#include "cocos2d.h"
class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	// implement the "static create()" method manually
	static GameScene* create() {
		GameScene* pRet = new(std::nothrow) GameScene();
		if (pRet && pRet->init()) {
			pRet->autorelease(); return pRet;
		}
		else {
			delete pRet;
			pRet = nullptr;
			return nullptr;
		}
	};
	void setLevelConfig(const std::string& levelConfig) {
		this->_levelConfig = levelConfig;
	}
	void GameScene::menuCloseCallback(Ref* pSender);
private:
	std::string _levelConfig;
};
