#pragma once
#include "basicscene.h"
USING_NS_CC_EXT;
class MainScene :
    public BasicScene
{
public:
    ~MainScene();
    static cocos2d::Scene* createScene();
    virtual bool init();  
    void createUI();
    CREATE_FUNC(MainScene);
    void onMouseEnd(Ref* psend,Widget::TouchEventType type);
    void skillbtn_event(Ref* pSender,Widget::TouchEventType type);


	void attackBack(){needStop = false;};

	void defevt(EventCustom* evt);
	virtual void OnBackCallBack();
	void playerDie(EventCustom* evt);
private:
	void delay();
    Layout* skill_layer;
    ListView* list;
//    LoadingBar* pro_1;
//    LoadingBar* pro_2;
    std::string lastName;
	Text* text;
	std::string str1;
	Vector<Button*> btnlist;

	Vec2 _initpos;
	Size _initSize;
	bool needStop;

};

