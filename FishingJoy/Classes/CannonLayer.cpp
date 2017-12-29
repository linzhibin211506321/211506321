//用来实现存放炮台和炮台切换按钮。
#include "CannonLayer.h"
#include "PersonalAudioEngine.h"

CannonLayer::CannonLayer(void)
{
}

CannonLayer::~CannonLayer(void)
{
}

bool CannonLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	_weapon = Weapon::create((CannonType)0);//通过Weapon ::create()方法创建出Weapon的对象赋值给_weapon。
	this->addChild(_weapon,1);
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();//通过导演类CCDirector的成员函数getWinSize()获取到应用程序的窗口大小。
	_weapon->setPosition(ccp(winSize.width/2 - 18, 0));//将武器位置设置到最底层中心位置。

	//创建出添加炮台的菜单项。
	_addMenuItem = CCMenuItemImage::create(
		"ui_button_66-ipadhd.png",
		"ui_button_66-ipadhd.png",
		this, menu_selector(CannonLayer::switchCannonCallback));

	//创建出减少炮台的菜单项。
	_subMenuItem = CCMenuItemImage::create(
		"ui_button_64-ipadhd.png",
		"ui_button_64-ipadhd.png",
		this, menu_selector(CannonLayer::switchCannonCallback));

	//调节菜单项的坐标。
	CCMenu* menu = CCMenu::create(_subMenuItem, _addMenuItem, NULL);
	menu->alignItemsHorizontallyWithPadding(120);
	addChild(menu,0);
	menu->setPosition(ccp(winSize.width/2-20, _addMenuItem->getContentSize().height/2));
	return true;
}

//切换当前的炮台类型。
void CannonLayer::switchCannonCallback(cocos2d::CCObject* sender)
{
	CannonOperate operate = k_Cannon_Operate_Up;
	if((CCMenuItemImage*)sender == _subMenuItem)
	{
		operate = k_Cannon_Operate_Down;
	}
	_weapon->changeCannon(operate);
	PersonalAudioEngine::sharedEngine()->playEffect("bgm_button.aif");//切换炮台时的音效
}

//旋转炮台，让炮口对准targe的方向
void CannonLayer::aimAt(CCPoint target)
{
	_weapon->aimAt(target);//旋转炮台。
}
//子弹对准targe的方向
bool CannonLayer::shootTo(CCPoint target)
{
	return _weapon->shootTo(target);//发射子弹。
}
