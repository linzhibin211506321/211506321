#include "FishLayer.h"

#include "Fish.h"

FishLayer::FishLayer(void)
{
}
FishLayer::~FishLayer(void)
{
}

CCScene* FishLayer::scene(void)
{
	CCScene* scene = CCScene::create();
	FishLayer* fishLayer = FishLayer::create();
	scene->addChild(fishLayer);
	return scene;
}

bool FishLayer::init()
{

	if(!CCLayer::init())
	{
		return false;
	}
	
	Fish *fish = Fish::create((FishType)3);
	if(!fish)
	{
		return false;
	}
	this->addChild(fish);
	fish->setPosition(ccp(1000,800));

	return true;
}



