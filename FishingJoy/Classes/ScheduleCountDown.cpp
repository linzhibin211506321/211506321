//根据传入的倒计时周期和是否循环构建倒计时组件。
#include "ScheduleCountDown.h"


ScheduleCountDown* ScheduleCountDown::create(ScheduleCounterDelegate* target, int perimeter, bool loop)//target: 倒计时时间到达后调用的协议对象；perimeter：计时周期；loop:计时周期到达后是否继续计时。
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
	this->schedule(schedule_selector(ScheduleCountDown::schedulePerSecond), 1.0f);//注册间隔1.0秒需要调用的函数
	return true;
}

//倒计时主要函数，每间隔1秒被调用到的函数。
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
