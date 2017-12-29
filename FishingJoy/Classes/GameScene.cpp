#include "GameScene.h"
#include "FishingJoyData.h"
#include "PersonalAudioEngine.h"

GameScene::GameScene()
{
}

bool GameScene::init()
{
	do
	{
		CC_BREAK_IF(!CCScene::init());

		_backgroundLayer = BackgroundLayer::create();
		CC_BREAK_IF(!_backgroundLayer);
		this->addChild(_backgroundLayer);

		_fishLayer = FishLayer::create();
		CC_BREAK_IF(!_fishLayer);
		this->addChild(_fishLayer);

		_cannonLayer = CannonLayer::create();
		CC_BREAK_IF(!_cannonLayer);
		this->addChild(_cannonLayer);

		_panelLayer = PanelLayer::create();
		CC_BREAK_IF(!_panelLayer);
		this->addChild(_panelLayer);

		_menuLayer = MenuLayer::create(); 
		CC_BREAK_IF(!_menuLayer);
		CC_SAFE_RETAIN(_menuLayer); 

		_touchLayer = TouchLayer::create();
		CC_BREAK_IF(!_touchLayer);
		this->addChild(_touchLayer);

		//增加设置初始金币数值到金币显示版中。
		int gold = FishingJoyData::sharedFishingJoyData()->getGold();//获取金币值。
		_panelLayer->getGoldCounter()->setNumber(gold);//将金币值设置到面板中。

		this->scheduleUpdate();
		PersonalAudioEngine::sharedEngine()->playBackgroundMusic("music_1.mp3");
		return true;
	} while (0);
	return false;
}


GameScene::~GameScene()
{
	CC_SAFE_RELEASE(_menuLayer);
}

//旋转炮台，让炮口对准targe的方向。
void GameScene::cannonAimAt(CCPoint target)
{
	_cannonLayer->aimAt(target);//旋转炮台。
}

//子弹对准targe的方向
void GameScene::cannonShootTo(CCPoint target)
{
	int type = _cannonLayer->getWeapon()->getCannon()->getType();
	int cost = (type+1) * 1;
	int currentGold = FishingJoyData::sharedFishingJoyData()->getGold();
	if(currentGold >= cost && _cannonLayer->shootTo(target)){//发射子弹。
		PersonalAudioEngine::sharedEngine()->playEffect("bgm_fire.aif");
		this->alterGold(-cost);//更新金币值
	}
}

//检查一颗子弹和多条鱼之间是否碰撞。
bool GameScene::checkOutCollisionBetweenFishesAndBullet(Bullet* bullet)
{
	CCPoint bulletPos = bullet->getCollosionPoint();//得到当前子弹的位置，并且保存到bulletPos中。
	CCArray* fishArray = _fishLayer->getFishArray();//得到鱼群数组，并且保存到fishArray中。
	CCObject* obj = NULL;
	//判断是否发生碰撞。
	CCARRAY_FOREACH(fishArray, obj)
	{
		Fish* fish =(Fish*)obj;
		if(fish->isRunning() && fish->getCollisionArea().containsPoint(bulletPos))
		{
			bullet->end();
			return true;
		}
	}
	return false;
}
//检查鱼跟鱼之间是否有碰撞发生。
void GameScene::checkOutCollision()
{
	CCArray* bullets = _cannonLayer->getWeapon()->getBullets();
	CCObject* obj = NULL;
	CCARRAY_FOREACH(bullets, obj)
	{
		Bullet* bullet = (Bullet*)obj;
		if(bullet->isVisible())
		{
			if(checkOutCollisionBetweenFishesAndBullet(bullet))
			{
				checkOutCollisionBetweenFishesAndFishingNet(bullet);
			}
		}
	}	
}

//帧更新函数。
void GameScene::update(float delta)
{
	checkOutCollision();
}

//计算鱼是否会被捉住。
void GameScene::fishWillBeCaught(Fish* fish)
{
	float weaponPercents[k_Cannon_Count] = { 0.3f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f};
	float fishPercents[	k_Fish_Type_Count] = { 1.0f, 0.9f, 0.8f, 0.7f, 0.6f, 0.5f};
	int cannonType = _cannonLayer->getWeapon()->getCannonType();
	int fishType = fish->getType();

	if(CCRANDOM_0_1() < weaponPercents[cannonType] * fishPercents[fishType>=6?6:fishType])//判断鱼是否被抓住。如果被抓住则播放被抓住的音效。并且金币增加。
	{
		fish->beCaught();
		PersonalAudioEngine::sharedEngine()->playEffect("bgm_net.mp3");
		int reward = (fishType+1)*10;
		this->alterGold(reward);//更新当前金币值
	}
}
//检测渔网是否有碰到鱼。
void GameScene::checkOutCollisionBetweenFishesAndFishingNet(Bullet* bullet)
{
	Weapon* weapon = _cannonLayer->getWeapon();
	CCRect rect = weapon->getCollisionArea(bullet);
	CCArray* fishArray = _fishLayer->getFishArray();
	CCObject* obj = NULL;
	CCARRAY_FOREACH(fishArray, obj)
	{
		Fish* fish = (Fish*)obj;
		if(fish->isRunning() && rect.intersectsRect(fish->getCollisionArea()))
		{
			fishWillBeCaught(fish);
		}
	}
}

//暂停或恢复指定节点及其孩子节点的所有动作。
void GameScene::operateAllSchedulerAndActions(CCNode* node, OperateFlag flag)//node：需要暂停或恢复动作的节点。flag：暂停还是恢复选项。
{
	if(node->isRunning()){
		switch (flag) {
		case k_Operate_Pause:
			node->pauseSchedulerAndActions();
			break;
		case k_Operate_Resume:
			node->resumeSchedulerAndActions();
			break;
		default:
			break;
		}
		CCArray* array = node->getChildren();
		if(array != NULL && array->count()>0){
			CCObject* iterator;
			CCARRAY_FOREACH(array, iterator){
				CCNode* child = (CCNode*)iterator;
				this->operateAllSchedulerAndActions(child, flag);
			}
		}
	}
}

//该成员函数完成游戏暂停的功能，并且弹出菜单层。
void GameScene::pause()
{
	PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
	PersonalAudioEngine::sharedEngine()->playEffect("bgm_button.aif");
	this->operateAllSchedulerAndActions(this, k_Operate_Pause);//暂停所有定时器和动画。
	_touchLayer->setTouchEnabled(false);
	this->addChild(_menuLayer);//将之前创建好的_menuLayer加入该层中。
}

void GameScene::resume()
{
	this->operateAllSchedulerAndActions(this, k_Operate_Resume);
	PersonalAudioEngine::sharedEngine()->resumeBackgroundMusic();
	this->removeChild(_menuLayer, false);
	_touchLayer->setTouchEnabled(true);
}

//更新金币数值。
void GameScene::alterGold(int delta)
{
	FishingJoyData::sharedFishingJoyData()->alterGold(delta);
	_panelLayer->getGoldCounter()->setNumber(FishingJoyData::sharedFishingJoyData()->getGold());
}

//倒计时周期到达后调用的函数
void GameScene::scheduleTimeUp()
{
	this->alterGold(200);
}
