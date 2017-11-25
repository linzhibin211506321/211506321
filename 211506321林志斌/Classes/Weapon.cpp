#include "Weapon.h"

#include "StaticData.h"
#define BULLET_COUNT 10

//Weapon::Weapon(void)
//{
//}
//
//
//Weapon::~Weapon(void)
//{
//}

Weapon *Weapon::create(CannonType type)
{
	Weapon *weapon = new Weapon();
	if(weapon && weapon->init(type))
	{
		weapon->autorelease();
		return weapon;
	}
	else
	{
		CC_SAFE_DELETE(weapon); 
		return NULL;
	}
}

bool Weapon::init(CannonType type)
{
	do
	{
		CC_BREAK_IF(!CCNode::init());
		_cannon=Cannon::create(type);
		CC_BREAK_IF(!_cannon);
		this->addChild(_cannon,1);
		_bullets=CCArray::createWithCapacity(BULLET_COUNT);
		CC_BREAK_IF(!_bullets);
		CC_SAFE_RETAIN(_bullets);
		_fishNets=CCArray::createWithCapacity(BULLET_COUNT);
		CC_BREAK_IF(!_fishNets);
		CC_SAFE_RETAIN(_fishNets);
		for(int i=0;i<BULLET_COUNT;i++)
		{
			Bullet *bullet = Bullet::create();
			_bullets->addObject(bullet);
			this->addChild(bullet);
			bullet->setVisible(false);
			FishNet *fishNet=FishNet::create();
			_fishNets->addObject(fishNet);
			this->addChild(fishNet);
			fishNet->setVisible(false);
			bullet->setUserObject(fishNet);
		}
		return true;
	}while(0);
	return false;
}
CCSize Weapon::getCannonSize()
{
	return _cannon->getSize();
}
CannonType Weapon::getCannonType()
{
	return _cannon->getType();
}
void Weapon::changeCannon(CannonOperate operate)
{
	int type=(int) _cannon->getType();
	type+=operate;
	_cannon->setType((CannonType)type);
}
Weapon::~Weapon()
{
	CC_SAFE_RELEASE(_bullets);
	CC_SAFE_RELEASE(_fishNets);
}


void Weapon::shootTo(CCPoint target)
{
	//CCLOG("1 x = %f y = %f",target.x,target.y);
	Bullet *bullet = getBulletToShoot();
	if(bullet == NULL)
	{
		return;
	}
	CCPoint pointWordSpace = getParent()->convertToWorldSpace(getPosition());
	float distance = ccpDistance(target,pointWordSpace);
	if(distance > _cannon->getFireRange())
	{
		CCPoint normal = ccpNormalize(ccpSub(target,pointWordSpace));
		CCPoint mult = ccpMult(normal,_cannon->getFireRange());
		//CCPoint mult = ccpMult(normal,distance);
		target = ccpAdd(pointWordSpace,mult);
	}
	//CCLOG("2 x = %f y = %f",target.x,target.y);
	bullet->flyTo(target,_cannon->getType());
}
Bullet *Weapon::getBulletToShoot()
{
	CCObject *obj;
	CCARRAY_FOREACH(_bullets,obj)
	{
			Bullet *bullet = (Bullet *)obj;
			if(bullet->isVisible()==false)
			{
				return bullet;
			}
	}
	return NULL;
}
void Weapon::aimAt(cocos2d::CCPoint target)
{
	//CCPoint location = getParent()->convertToWorldSpace(getPosition());
	//float angle = ccpAngleSigned(ccpSub(target,location),CCPointMake(0,1));
	//this->setRotation(CC_RADIANS_TO_DEGREES(angle));
	//CCLOG("targetX:",target.x);
	//CCLOG("targetY:",target.y);
	_cannon->aimAt(target);
}