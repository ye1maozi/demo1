#pragma once
#include "cocos2d.h"
USING_NS_CC;
class msgBox :
	public LayerColor
{
public:
	msgBox();
	~msgBox();

	virtual bool onInitDialog(const ccMenuCallback& callback)=0 ;
	void pushMenu(CCMenuItem* pMenu);

	virtual bool init(const ccMenuCallback& callback);
	virtual void onEnter();
	virtual void onExit();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	virtual void onTouchCancelled(Touch *touch, Event *unused_event);
protected:
	static bool isOpen;
private:


	bool initMenu();

	Menu* mMenu;
//	Vector<MenuItem*> mMenuItemArray;
	bool mTouchMenu;
};

