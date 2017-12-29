//���ݴ���ĵ���ʱ���ں��Ƿ�ѭ����������ʱ�����
#include "ScheduleCountDown.h"


ScheduleCountDown* ScheduleCountDown::create(ScheduleCounterDelegate* target, int perimeter, bool loop)//target: ����ʱʱ�䵽�����õ�Э�����perimeter����ʱ���ڣ�loop:��ʱ���ڵ�����Ƿ������ʱ��
{
	ScheduleCountDown* counter = new ScheduleCountDown();
	counter->init(target, perimeter, loop);
	counter->autorelease();
	return counter;
}

bool ScheduleCountDown::init(ScheduleCounterDelegate* target, int perimeter, bool loop)
{
	_target = target;
	_maxTime = perimeter;
	_currTime = perimeter;
	_loop = loop;
	this->schedule(schedule_selector(ScheduleCountDown::schedulePerSecond), 1.0f);//ע����1.0����Ҫ���õĺ���
	return true;
}

//����ʱ��Ҫ������ÿ���1�뱻���õ��ĺ�����
void ScheduleCountDown::schedulePerSecond(float delta)
{
	_currTime--;
	if(_currTime <= 0){
		bool isLoop = this->getLoop();
		if(isLoop){
			_currTime = _maxTime;
		}else{
			this->unschedule(schedule_selector(ScheduleCountDown::schedulePerSecond));
		}
		_target->scheduleTimeUp();
	}
	_target->setScheduleNumber(_currTime);
}
