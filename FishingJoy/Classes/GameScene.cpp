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

		//�������ó�ʼ�����ֵ�������ʾ���С�
		int gold = FishingJoyData::sharedFishingJoyData()->getGold();//��ȡ���ֵ��
		_panelLayer->getGoldCounter()->setNumber(gold);//�����ֵ���õ�����С�

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

//��ת��̨�����ڿڶ�׼targe�ķ���
void GameScene::cannonAimAt(CCPoint target)
{
	_cannonLayer->aimAt(target);//��ת��̨��
}

//�ӵ���׼targe�ķ���
void GameScene::cannonShootTo(CCPoint target)
{
	int type = _cannonLayer->getWeapon()->getCannon()->getType();
	int cost = (type+1) * 1;
	int currentGold = FishingJoyData::sharedFishingJoyData()->getGold();
	if(currentGold >= cost && _cannonLayer->shootTo(target)){//�����ӵ���
		PersonalAudioEngine::sharedEngine()->playEffect("bgm_fire.aif");
		this->alterGold(-cost);//���½��ֵ
	}
}

//���һ���ӵ��Ͷ�����֮���Ƿ���ײ��
bool GameScene::checkOutCollisionBetweenFishesAndBullet(Bullet* bullet)
{
	CCPoint bulletPos = bullet->getCollosionPoint();//�õ���ǰ�ӵ���λ�ã����ұ��浽bulletPos�С�
	CCArray* fishArray = _fishLayer->getFishArray();//�õ���Ⱥ���飬���ұ��浽fishArray�С�
	CCObject* obj = NULL;
	//�ж��Ƿ�����ײ��
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
//��������֮���Ƿ�����ײ������
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

//֡���º�����
void GameScene::update(float delta)
{
	checkOutCollision();
}

//�������Ƿ�ᱻ׽ס��
void GameScene::fishWillBeCaught(Fish* fish)
{
	float weaponPercents[k_Cannon_Count] = { 0.3f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f};
	float fishPercents[	k_Fish_Type_Count] = { 1.0f, 0.9f, 0.8f, 0.7f, 0.6f, 0.5f};
	int cannonType = _cannonLayer->getWeapon()->getCannonType();
	int fishType = fish->getType();

	if(CCRANDOM_0_1() < weaponPercents[cannonType] * fishPercents[fishType>=6?6:fishType])//�ж����Ƿ�ץס�������ץס�򲥷ű�ץס����Ч�����ҽ�����ӡ�
	{
		fish->beCaught();
		PersonalAudioEngine::sharedEngine()->playEffect("bgm_net.mp3");
		int reward = (fishType+1)*10;
		this->alterGold(reward);//���µ�ǰ���ֵ
	}
}
//��������Ƿ��������㡣
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

//��ͣ��ָ�ָ���ڵ㼰�亢�ӽڵ�����ж�����
void GameScene::operateAllSchedulerAndActions(CCNode* node, OperateFlag flag)//node����Ҫ��ͣ��ָ������Ľڵ㡣flag����ͣ���ǻָ�ѡ�
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

//�ó�Ա���������Ϸ��ͣ�Ĺ��ܣ����ҵ����˵��㡣
void GameScene::pause()
{
	PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
	PersonalAudioEngine::sharedEngine()->playEffect("bgm_button.aif");
	this->operateAllSchedulerAndActions(this, k_Operate_Pause);//��ͣ���ж�ʱ���Ͷ�����
	_touchLayer->setTouchEnabled(false);
	this->addChild(_menuLayer);//��֮ǰ�����õ�_menuLayer����ò��С�
}

void GameScene::resume()
{
	this->operateAllSchedulerAndActions(this, k_Operate_Resume);
	PersonalAudioEngine::sharedEngine()->resumeBackgroundMusic();
	this->removeChild(_menuLayer, false);
	_touchLayer->setTouchEnabled(true);
}

//���½����ֵ��
void GameScene::alterGold(int delta)
{
	FishingJoyData::sharedFishingJoyData()->alterGold(delta);
	_panelLayer->getGoldCounter()->setNumber(FishingJoyData::sharedFishingJoyData()->getGold());
}

//����ʱ���ڵ������õĺ���
void GameScene::scheduleTimeUp()
{
	this->alterGold(200);
}
