#pragma once
//#include "d:\c++实训\c++实训软件工具\cocos2d-x-2.2.5\cocos2dx\layers_scenes_transitions_nodes\ccscene.h"

#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "FishLayer.h"
#include "MenuLayer.h"

//17-11-19
#include "TouchLayer.h"
#include "CannonLayer.h"
USING_NS_CC;

class GameScene :
	public CCScene
{
public:
	GameScene(void);
	
	CREATE_FUNC(GameScene)
	virtual bool init();

	static CCScene* scene(void);

	virtual ~GameScene(void);

	//11-19添加

	void cannonAimAt(CCPoint target);
	void cannonShootTo(CCPoint target);
protected:
	BackgroundLayer *backgroundLayer;
	FishLayer *fishLayer;
	MenuLayer *menuLayer;

	//11-19
	//PaneLayer *_paneLayer;
	CannonLayer *_cannonLayer;
	TouchLayer *_touchLayer;

	void preloadResources(void);
};

