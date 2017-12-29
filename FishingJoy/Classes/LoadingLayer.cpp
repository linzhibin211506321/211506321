#include "LoadingLayer.h"
#include "GameScene.h"
#include "PersonalAudioEngine.h"
#include "FishingJoyData.h"

LoadingLayer::LoadingLayer(void)
{
	_loadedSp = 0;
	_numSp = 3;
	_progressBar = NULL;
	_progressFg = NULL;
}

CCScene* LoadingLayer::scene(void)
{
	CCScene* scene = CCScene::create();
	LoadingLayer* loadingLayer = LoadingLayer::create();
	scene->addChild(loadingLayer);
	return scene;
}


//层加载时调用到的接口
bool LoadingLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* background = CCSprite::create("loading_1-ipadhd.png");
	background->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.6));
	this->addChild(background);
	this->initProgressBar();
	this->scheduleOnce(schedule_selector(LoadingLayer::cacheInit), 0.5f);
	return true;
}

//对进度条的初始化
void LoadingLayer::initProgressBar()
{
	CCSprite* progressBg = CCSprite::create("loading_3-ipadhd.png");
	_progressFg = CCLabelTTF::create("", "Thonburi", 55);
	_progressFg->setColor(ccc3(197, 118, 20));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_progressBar = ProgressBar::create(this, CCSprite::create("loading_2-ipadhd.png"));
	_progressBar->setBackground(progressBg);//设置进度条背景
	_progressBar->setForeground(_progressFg);//设置进度条前景
	_progressBar->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.25));//设置进度条位置
	_progressBar->setSpeed(200.0f);//设置进度条速度
	this->addChild(_progressBar);
}

//进度条滚动过程中要更新的信息。
void LoadingLayer::progressPercentageSetter(float percentage)
{
	CCString* str = CCString::createWithFormat("", (int)percentage);
	_progressFg->setString(str->getCString());
}

//进度条移动结束。
void LoadingLayer::loadingFinished()
{
	CCScene* gameScene = GameScene::create();	
	CCDirector::sharedDirector()->replaceScene(gameScene);
}

//预加载资源。
void LoadingLayer::cacheInit(float delta)
{
	CCSpriteFrameCache* spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	int progressStart = 1;

	float ratio = 3.3f;

	char fishPlists[][50] = { "FishActor-Large-ipadhd.plist", "FishActor-Marlin-ipadhd.plist", 
		"FishActor-Shark-ipadhd.plist", "FishActor-Small-ipadhd.plist", "FishActor-Mid-ipadhd.plist", 
		"cannon-ipadhd.plist", "Item-chaojiwuqi-ipadhd.plist","UI_GameMenuText_cn-ipadhd.plist"};

	for (int i = 0; i < 7; i++)
	{
		spriteFrameCache->addSpriteFramesWithFile(fishPlists[i]);
		_progressBar->progressTo(ratio*(progressStart++));
	}

	CCTextureCache* textureCache = CCTextureCache::sharedTextureCache();

	char buttonTextures[][50] = { "ui_button_63-ipadhd.png", "ui_button_65-ipadhd.png",
		"ui_button_music_1-ipadhd.png", "ui_button_music_2-ipadhd.png", "button_other_001-ipadhd.png",
		"button_other_002-ipadhd.png", "button_other_003-ipadhd.png", "button_other_004-ipadhd.png"
	};

	for (int i = 0; i < 10; i++)
	{
		textureCache->addImage(buttonTextures[i]);
		_progressBar->progressTo(ratio*(progressStart++));
	}

	char str[][50] = { "SmallFish", "Croaker", "AngelFish", "Amphiprion", "PufferS", 
		"Bream", "Porgy", "Chelonian", "Lantern", "Ray", "Shark", "GoldenTrout", "GShark", 
		"GMarlinsFish", "GrouperFish", "JadePerch", "MarlinsFish", "PufferB" };
	for (int i = 0; i < 18; i++)
	{
		CCArray* array = CCArray::createWithCapacity(10);
		for (int j = 0; j < 10; j++)
		{
			CCString* spriteFrameName = CCString::createWithFormat("%s_actor_%03d.png", str[i], j + 1);
			CCSpriteFrame* spriteFrame = spriteFrameCache->spriteFrameByName(spriteFrameName->getCString());
			CC_BREAK_IF(!spriteFrame);
			array->addObject(spriteFrame);
		}
		if (array->count() == 0)
		{
			continue;
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(array, 0.15f);
		CCString* animationName = CCString::createWithFormat("fish_animation_%02d", i + 1);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, animationName->getCString());
		_progressBar->progressTo(ratio*(progressStart++));
	}

	PersonalAudioEngine::sharedEngine();
	FishingJoyData::sharedFishingJoyData();

	_progressBar->progressTo(100.0f);
}

LoadingLayer::~LoadingLayer(void)
{
}
