#include "msgBox.h"
#include "LSLog.h"
bool msgBox::isOpen=false;
msgBox::msgBox():mMenu(NULL),mTouchMenu(false)
{

}
msgBox::~msgBox()
{

	isOpen = false;
	CC_SAFE_RELEASE_NULL(mMenu);
//	mMenuItemArray.clear();
	LSLog::info("~msgBox");
}
bool msgBox::init(const ccMenuCallback& callback)
{
	bool ret = false;

	do
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(Color4B(0,0,0,255)));
		onInitDialog(callback);
		initMenu();
		ret = true;
	}
	while(0);
	return ret;
}

void msgBox::pushMenu(CCMenuItem* pMenu)
{
//	if(mMenuItemArray)
//	{
	//	mMenuItemArray.pushBack(pMenu);
//	}
}
bool msgBox::initMenu()
{
//	if(mMenuItemArray && mMenuItemArray->count() > 0)
//	{
		if(!mMenu)
		{
//			mMenu = Menu::createWithArray(mMenuItemArray);
//			mMenu->setPosition(CCPointZero);
//			addChild(mMenu);
		}
//	}
	return true;
}


void msgBox::onEnter()
{
	CCLayerColor::onEnter();

//	auto evt = EventListenerTouchOneByOne::create();
//	evt->onTouchBegan = CC_CALLBACK_2(msgBox::onTouchBegan,this);
//	evt->onTouchEnded = CC_CALLBACK_2(msgBox::onTouchEnded,this);
//	evt->onTouchMoved = CC_CALLBACK_2(msgBox::onTouchMoved,this);
//	evt->onTouchCancelled = CC_CALLBACK_2(msgBox::onTouchCancelled,this);

	this->setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	this->setSwallowsTouches(true);


//	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(evt,-129 );
}

void msgBox::onExit()
{
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this,true);
	CCLayerColor::onExit();
}

bool msgBox::onTouchBegan(Touch* touch ,Event* evt)
{
	//LSLog::info("111");
//	mTouchMenu = mMenu->ccTouchBegan(touch,evt);
	return true;
}

void msgBox::onTouchCancelled(Touch* touch ,Event* evt)
{
	if(mTouchMenu)
	{
//		mMenu->ccTouchMoved(touch,evt);
		mTouchMenu = false;
	}
}
void msgBox::onTouchMoved(Touch *touch, Event *unused_event)
{
	if(mTouchMenu)
	{
//		mMenu->ccTouchMoved(touch,unused_event);
	}
}

void msgBox::onTouchEnded(Touch *touch, Event *unused_event)
{
	//LSLog::info("222");
	if(mTouchMenu)
	{
//		mMenu->ccTouchMoved(touch,unused_event);
		mTouchMenu = false;
	}
}

