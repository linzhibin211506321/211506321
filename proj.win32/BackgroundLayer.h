#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d;
class BackgroundLayer:public CCLayer
{
public:
	BackgroundLayer(void);
	static BackgroundLayer *create()
	{
		BackgroundLayer *layer = new BackgroundLayer;
		/*CREATE_FUNC(BackgroundLayer);*/
		if(layer && layer->init())
		{
			layer->autorelease();
			return layer;
		}
		else
		{
			delete layer;
			layer = NULL;
			return NULL;
		}
	}
	virtual bool init();
	virtual ~BackgroundLayer(void);
};
