//集中接受和识别触摸事件，然后回传给GameScene进行处理。
//游戏运行时单击某个位置，炮台会根据这个位置进行旋转，使炮口朝向这个位置。
#include "TouchLayer.h"
#include "GameScene.h"

TouchLayer::TouchLayer(void)
{
}

TouchLayer::~TouchLayer(void)
{
}

void TouchLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector() -> getTouchDispatcher() -> addTargetedDelegate(this, 0, true);//加入触摸事件，触摸消息处理后不再传播。
}

bool TouchLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	setTouchEnabled(true);

	return true;
}

//重定义基类的虚函数，当触摸开始时触发的事件。
bool TouchLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	GameScene* gameScene = getGameScene();
	CCPoint target = pTouch->getLocation();
	gameScene->cannonAimAt(target);
	return true;
}

//当触摸移动时触发的事件。
void TouchLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	GameScene* gameScene = getGameScene();
	CCPoint target = pTouch->getLocation();//得到当前触摸点的坐标并且保存到target中。
	gameScene->cannonAimAt(target);
}

//触摸结束时触发的事件。
void TouchLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	GameScene* gameScene = getGameScene();
	CCPoint target = pTouch->getLocation();
	gameScene->cannonShootTo(target);
}

//获得游戏场景的指针。
GameScene* TouchLayer::getGameScene()
{
	return (GameScene*)getParent();
}