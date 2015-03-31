#pragma once
#include "basicscene.h"
class JoinScene :
	public BasicScene
{
public:
	enum MsgType
	{
		msg_help,
		msg_about,
	};
	~JoinScene();

	static cocos2d::Scene* createScene();
    virtual bool init();  
	
	virtual void createUI();
	 CREATE_FUNC(JoinScene);
	 void onExit();
	 void onMouseEnd(Ref* psend,Widget::TouchEventType type);
	 void onCheckBos(Ref* psend,CheckBox::EventType type);

	virtual void OnBackCallBack();

private:
	MsgType _lastMsg;
	Layout* bglayer;
	Layout* firstlayer;
	Layout* secondlayer;
	Layout* setlayer;

	ActionObject* ani;


	Text* label;

	void showMsg(MsgType type);
	
};

