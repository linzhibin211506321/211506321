//各种武器的管理类，通过该类的来获取各种武器
#include "Weapon.h"

#define BULLET_COUNT 6

//根据炮的类型生成炮的对象，还有其他各种武器对象。
Weapon* Weapon::create(CannonType type)
{
	Weapon* weapon = new Weapon();
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

//创建出武器相关的各种对象。
bool Weapon::init(CannonType type)
{
	do
	{
		CC_BREAK_IF(!CCNode::init());
		_cannon = Cannon::create(type);
		CC_BREAK_IF(!_cannon);
		addChild(_cannon, 1);
		
		_bullets = CCArray::createWithCapacity(BULLET_COUNT);
		CC_BREAK_IF(!_bullets);
		CC_SAFE_RETAIN(_bullets);
		
		_fishNets = CCArray::createWithCapacity(BULLET_COUNT);
		CC_BREAK_IF(!_fishNets);
		CC_SAFE_RETAIN(_fishNets);

		_particils = CCArray::createWithCapacity(BULLET_COUNT);
		CC_BREAK_IF(!_particils);
		CC_SAFE_RETAIN(_particils);
		
		//将子弹限制在自己所设置的数量之内
		for(int i = 0; i < BULLET_COUNT; i++)
		{
			Bullet* bullet = Bullet::create();
			_bullets->addObject(bullet);
			this->addChild(bullet);
			bullet->setVisible(false);
			
			FishNet* fishNet = FishNet::create();
			_fishNets->addObject(fishNet);
			this->addChild(fishNet);
			fishNet->setVisible(false);
			bullet->setUserObject(fishNet);

			CCParticleSystemQuad *particle = CCParticleSystemQuad::create("yuwanglizi.plist");
			particle->stopSystem();
			this->addChild(particle);
			_particils->addObject(particle);

			fishNet->setUserObject(particle);
		}
		return true;
	}while(0);

	return false;
}

//获得当前炮台精灵的大小。
CCSize Weapon::getCannonSize()
{
	return _cannon->getSize();
}

CannonType Weapon::getCannonType()
{
	return _cannon->getType();
}
                       
//实现变换炮台。
void Weapon::changeCannon(CannonOperate operate)
{
	int type = (int) _cannon->getType();
	type += operate;
	_cannon->setType((CannonType)type);
}

Weapon::~Weapon(void)
{
	CC_SAFE_RELEASE(_bullets);
	CC_SAFE_RELEASE(_fishNets);
	CC_SAFE_RELEASE(_particils);
}

//旋转炮台，让炮口对准targe的方向。target：用户在屏幕触摸的位置。
void Weapon::aimAt(CCPoint target)
{
	_cannon->aimAt(target);//旋转炮台。
}
//根据当前炮类型，调整目标坐标。
bool Weapon::shootTo(CCPoint target)
{
	Bullet* bullet= getBulletToShoot();
	if(bullet == NULL){
		return false;
	}
	CCPoint pointWorldSpace = getParent()->convertToWorldSpace(getPosition());
	float distance = ccpDistance(target, pointWorldSpace);//根据炮的类型计算子弹飞行的距离。
	if(distance > _cannon->getFireRange())
	{
		CCPoint normal = ccpNormalize(ccpSub(target, pointWorldSpace));
		CCPoint mult = ccpMult(normal, _cannon->getFireRange());//算出x轴和y轴的偏移值，并且保存到 mult中。
		target = ccpAdd(pointWorldSpace, mult);//在自己的现在坐标加上偏移值，算出子弹的目标位置，并且保存到target中。
	}
	bullet->flyTo(target, _cannon->getType());//发射子弹。
}

//获取当前可用的子弹。
Bullet* Weapon::getBulletToShoot()
{
	CCObject* obj;
	CCARRAY_FOREACH(_bullets, obj)
	{
		Bullet* bullet = (Bullet*)obj;
		if(!bullet->isVisible())
		{
			return bullet;
		}
	}
	return NULL;
}

//返回渔网的所在区域。
CCRect Weapon::getCollisionArea(Bullet *bullet)
{
	FishNet *_fishNets = (FishNet *)bullet->getUserObject();
	if(_fishNets->isVisible())
	{
		return _fishNets->getCollisionArea();
	}
	return CCRectZero;
}