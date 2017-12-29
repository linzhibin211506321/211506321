#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer(void)
{
}

bool BackgroundLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	CCSprite *bgSprite = CCSprite::create("bj03_01-ipadhd.png");
	this->addChild(bgSprite);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	bgSprite->setPosition(CCPoint(winSize.width * 0.5, winSize.height * 0.5));
	return true;
}

BackgroundLayer::~BackgroundLayer(void)
{
}
