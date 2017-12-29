//���������Ĺ����࣬ͨ�����������ȡ��������
#include "Weapon.h"

#define BULLET_COUNT 6

//�����ڵ����������ڵĶ��󣬻�������������������
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

//������������صĸ��ֶ���
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
		
		//���ӵ��������Լ������õ�����֮��
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

//��õ�ǰ��̨����Ĵ�С��
CCSize Weapon::getCannonSize()
{
	return _cannon->getSize();
}

CannonType Weapon::getCannonType()
{
	return _cannon->getType();
}
                       
//ʵ�ֱ任��̨��
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

//��ת��̨�����ڿڶ�׼targe�ķ���target���û�����Ļ������λ�á�
void Weapon::aimAt(CCPoint target)
{
	_cannon->aimAt(target);//��ת��̨��
}
//���ݵ�ǰ�����ͣ�����Ŀ�����ꡣ
bool Weapon::shootTo(CCPoint target)
{
	Bullet* bullet= getBulletToShoot();
	if(bullet == NULL){
		return false;
	}
	CCPoint pointWorldSpace = getParent()->convertToWorldSpace(getPosition());
	float distance = ccpDistance(target, pointWorldSpace);//�����ڵ����ͼ����ӵ����еľ��롣
	if(distance > _cannon->getFireRange())
	{
		CCPoint normal = ccpNormalize(ccpSub(target, pointWorldSpace));
		CCPoint mult = ccpMult(normal, _cannon->getFireRange());//���x���y���ƫ��ֵ�����ұ��浽 mult�С�
		target = ccpAdd(pointWorldSpace, mult);//���Լ��������������ƫ��ֵ������ӵ���Ŀ��λ�ã����ұ��浽target�С�
	}
	bullet->flyTo(target, _cannon->getType());//�����ӵ���
}

//��ȡ��ǰ���õ��ӵ���
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

//������������������
CCRect Weapon::getCollisionArea(Bullet *bullet)
{
	FishNet *_fishNets = (FishNet *)bullet->getUserObject();
	if(_fishNets->isVisible())
	{
		return _fishNets->getCollisionArea();
	}
	return CCRectZero;
}