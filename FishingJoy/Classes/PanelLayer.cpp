//实现暂停的功能。
#include "PanelLayer.h"
#include "GameScene.h"
#include "ScheduleCountDown.h"
PanelLayer::PanelLayer(void)
{

}

PanelLayer::~PanelLayer(void)
{

}

//初始化，添加菜单项，菜单，金币，倒计时。
bool PanelLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_goldCounter = GoldCounterLayer::create(0);
	addChild(_goldCounter);
    _goldCounter->setPosition(ccp(50,1200));//金币所在的位置

	ScheduleCountDown* countDown = ScheduleCountDown::create(this);
	_scheduleLabel = CCLabelTTF::create("60", "Thonburi", 70);//倒计时
	_scheduleLabel->addChild(countDown);
	this->addChild(_scheduleLabel);
	_scheduleLabel->setPosition(ccp(50, 1250));//倒计时所在的位置

	CCMenuItemSprite* pause = CCMenuItemSprite::create(CCSprite::create("button_other_003-ipadhd.png"), 
							CCSprite::create("button_other_004-ipadhd.png"),
							this, menu_selector(PanelLayer::pause));

	CCMenu* menu = CCMenu::create(pause, NULL);
	this->addChild(menu);

	CCSize pauseSize = pause->getContentSize();
	menu->setPosition(CCPointMake(winSize.width-pauseSize.width*0.5, pauseSize.height*0.5));

	return true;
}

//该层暂停菜单的响应函数。
void PanelLayer::pause(CCObject *sender)
{
	GameScene* gameScene = (GameScene*)this->getParent();
	gameScene->pause();
}

//按照指定的长度从连接方接收数据到data中。
void PanelLayer::setScheduleNumber(int number)
{
	_scheduleLabel->setString(CCString::createWithFormat("%d",number)->getCString());
}

//倒计时周期到达后调用的函数。
void PanelLayer::scheduleTimeUp()
{
	_scheduleLabel->setVisible(false);
	GameScene* gameScene = (GameScene*)this->getParent();
	gameScene->scheduleTimeUp();
}
