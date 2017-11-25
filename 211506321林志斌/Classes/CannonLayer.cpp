#include "CannonLayer.h"

#include "Weapon.h"
#include "Bullet.h"
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
	_weapon = Weapon::create((CannonType)0);
	
	addChild(_weapon,1);
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();

	_weapon->setPosition(ccp(winSize.width/2-18,0));
	_addMenuItem=CCMenuItemImage::create(
		"ui_button_65-ipadhd.png",
		"ui_button_65-ipadhd.png",
		this,menu_selector(CannonLayer::switchCannonCallback));
	_subMenuItem=CCMenuItemImage::create(
			"ui_button_63-ipadhd.png",
			"ui_button_63-ipadhd.png",
			this,menu_selector(CannonLayer::switchCannonCallback));
	CCMenu *menu = CCMenu::create(_subMenuItem,_addMenuItem,NULL);
	menu->alignItemsHorizontallyWithPadding(120);
	addChild(menu,0);


	menu->setPosition(ccp(winSize.width/2-20,_addMenuItem->getContentSize().height/2));
	return true;
}
void CannonLayer::switchCannonCallback(cocos2d::CCObject *sender)
{
	CannonOperate operate=k_Cannon_Operate_Up;
	if((CCMenuItemImage *)sender==_subMenuItem)
	{
		operate=k_Cannon_Operate_Down;
	}
	_weapon->changeCannon(operate);

}

//11-19
void CannonLayer::aimAt(cocos2d::CCPoint target)
{
	//CCPoint location = getParent()->convertToWorldSpace(getPosition());
	//float angle = ccpAngleSigned(ccpSub(target,location),CCPointMake(0,1));
	//this->setRotation(CC_RADIANS_TO_DEGREES(angle));
	_weapon->aimAt(target);
}
void CannonLayer::shootTo(cocos2d::CCPoint target)
{
	//CCLOG("1 x = %f y = %f",target.x,target.y);
	//Bullet *bullet = getBulletToShoot();
	//if(bullet == NULL)
	//{
	//	return;
	//}
	//CCPoint pointWordSpace = getParent()->convertToWorldSpace(getPosition());
	//float distance = ccpDistance(target,pointWordSpace);
	//if(distance > _cannon->getFireRange())
	//{
	//	CCPoint normal = ccpNormalize(ccpSub(target,pointWordSpace));
	//	CCPoint mult = ccpMult(normal,_cannon->getFireRange());
	//	target = ccpAdd(pointWordSpace,mult);
	//}
	//CCLOG("2 x = %f y = %f",target.x,target.y);
	//bullet->flyTo(target,_cannon->getType());
	_weapon->shootTo(target);
}
	
