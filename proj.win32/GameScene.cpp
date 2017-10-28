#include "GameScene.h"


GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
	CC_SAFE_RELEASE_NULL(menuLayer);
}

bool GameScene::init()
{
	do
	{
		if(!CCScene::init())
		{
			break;
		}
		backgroundLayer = BackgroundLayer::create();
		CC_BREAK_IF(!backgroundLayer);
		this->addChild(backgroundLayer);

		fishLayer = FishLayer::create();
		if(!fishLayer)
		{
			break;
		}
		this->addChild(fishLayer);

		menuLayer = MenuLayer::create();
		CC_BREAK_IF(!menuLayer);
		CC_SAFE_RETAIN(menuLayer);
		return true;
	}while(0);
	return false;
}