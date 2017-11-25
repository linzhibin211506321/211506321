#pragma once
//#include "d:\c++ʵѵ\c++\cocos2d-x-2.2.5\cocos2dx\layers_scenes_transitions_nodes\cclayer.h"
#include "cocos2d.h"
USING_NS_CC;
class GameScene;
class TouchLayer :
	public CCLayer
{
public:
	TouchLayer(void);
	virtual ~TouchLayer(void);

	CREATE_FUNC(TouchLayer);
	//virtual bool init();
	bool init();
protected:
	virtual bool ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch,CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch,CCEvent *pEvent);
	virtual void registerWithTouchDispatcher();
	GameScene *getGameScene();
};

