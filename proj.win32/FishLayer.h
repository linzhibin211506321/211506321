#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class FishLayer:public CCLayer
{
public:
	FishLayer(void);
	CREATE_FUNC(FishLayer)
	virtual bool init();
	virtual ~FishLayer(void);
};