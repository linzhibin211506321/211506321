#pragma once
#define _BULLET_H
#include "cocos2d.h"

USING_NS_CC;
class Bullet :
	public CCNode
{
public:
	Bullet(void);
	virtual ~Bullet(void);
	
	CREATE_FUNC(Bullet);
	bool init();

	//11-19
	void end();
	//void flyTo(CCPoint targetInWorldSpace,int type );
	void flyTo(CCPoint targetInWorldSpace,int type=0);
	//CCPoint getCollisionPoint();

protected:
	float getSpeed(int type);
	CCSprite *_bulletSprite;
};

