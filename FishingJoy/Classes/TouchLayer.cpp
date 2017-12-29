//���н��ܺ�ʶ�����¼���Ȼ��ش���GameScene���д���
//��Ϸ����ʱ����ĳ��λ�ã���̨��������λ�ý�����ת��ʹ�ڿڳ������λ�á�
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
	CCDirector::sharedDirector() -> getTouchDispatcher() -> addTargetedDelegate(this, 0, true);//���봥���¼���������Ϣ������ٴ�����
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

//�ض��������麯������������ʼʱ�������¼���
bool TouchLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	GameScene* gameScene = getGameScene();
	CCPoint target = pTouch->getLocation();
	gameScene->cannonAimAt(target);
	return true;
}

//�������ƶ�ʱ�������¼���
void TouchLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	GameScene* gameScene = getGameScene();
	CCPoint target = pTouch->getLocation();//�õ���ǰ����������겢�ұ��浽target�С�
	gameScene->cannonAimAt(target);
}

//��������ʱ�������¼���
void TouchLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	GameScene* gameScene = getGameScene();
	CCPoint target = pTouch->getLocation();
	gameScene->cannonShootTo(target);
}

//�����Ϸ������ָ�롣
GameScene* TouchLayer::getGameScene()
{
	return (GameScene*)getParent();
}